#include <vector>
#include <memory>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <omp.h>
#include <cassert>

namespace ecs {
    template <typename T, size_t Align = 32>
    using AlignedVector = std::vector<T,
        std::conditional_t<Align <= alignof(std::max_align_t),
        std::allocator<T>,
        std::allocator<T>>>;  // 实际项目应使用自定义对齐分配器

    struct EntityData {
        AlignedVector<float> x;
        AlignedVector<float> y;
        AlignedVector<float> dx;
        AlignedVector<float> dy;

        explicit EntityData(size_t count) :
            x(count, 0.0f),
            y(count, 0.0f),
            dx(count, 1.0f),
            dy(count, 0.5f)
        {
            // 确保内存对齐（MSVC 2022保证vector内存至少16字节对齐）
            assert(reinterpret_cast<uintptr_t>(x.data()) % 32 == 0);
            assert(reinterpret_cast<uintptr_t>(dx.data()) % 32 == 0);
        }
    };

    class World {
        std::unique_ptr<EntityData> data;
        size_t size;

        static constexpr size_t SIMD_WIDTH = 8; // AVX2处理8个float

    public:
        void create_entities(size_t count) {
            size = count;
            data = std::make_unique<EntityData>(count);
        }

        __declspec(noinline) void movement_system() noexcept {
            const auto* dx = data->dx.data();
            const auto* dy = data->dy.data();
            auto* x = data->x.data();
            auto* y = data->y.data();

            // 主循环向量化处理
//#pragma omp parallel for simd schedule(static) aligned(x, y, dx, dy:32)
#pragma omp parallel for
            for (int64_t i = 0; i < static_cast<int64_t>(size); ++i) {
                x[i] += dx[i];
                y[i] += dy[i];
            }
        }
    };
}

int main() {
    constexpr size_t ENTITY_COUNT = 10'000'000;
    constexpr size_t ITERATIONS = 100;
    ecs::World world;

    // 实体创建计时
    auto create_start = std::chrono::high_resolution_clock::now();
    world.create_entities(ENTITY_COUNT);
    auto create_time = std::chrono::high_resolution_clock::now() - create_start;
    std::cout << "Entities created in "
        << std::chrono::duration_cast<std::chrono::microseconds>(create_time).count()
        << " μs\n";

    // 预热运行
    for (int i = 0; i < 5; ++i) {
        world.movement_system();
    }

    // 基准测试
    std::chrono::nanoseconds total_time{ 0 };
    for (size_t i = 0; i < ITERATIONS; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        world.movement_system();
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        total_time += elapsed;

        if ((i + 1) % 10 == 0) {
            std::cout << "Iteration " << (i + 1) << ": "
                << std::fixed << std::setprecision(4)
                << (elapsed.count() / 1e6) << " ms\n";
        }
    }

    // 统计结果
    const double avg_time = total_time.count() / static_cast<double>(ITERATIONS);
    const double per_entity = avg_time / ENTITY_COUNT;
    const double throughput = ENTITY_COUNT / (avg_time / 1e9) / 1e6;

    std::cout << "\nAverage per entity: " << std::fixed << std::setprecision(6)
        << per_entity << " ns/entity\n";
    std::cout << "Throughput: " << std::fixed << std::setprecision(2)
        << throughput << " M entities/sec\n";

    return 0;
}