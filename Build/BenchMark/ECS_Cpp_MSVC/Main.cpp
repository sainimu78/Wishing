#include <vector>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <immintrin.h>

#ifdef _MSC_VER
#define ALIGNED_ALLOC(size, align) _aligned_malloc(size, align)
#define ALIGNED_FREE(ptr) _aligned_free(ptr)
#else
#define ALIGNED_ALLOC(size, align) aligned_alloc(align, size)
#define ALIGNED_FREE(ptr) free(ptr)
#endif

class World {
public:
    float* x;
    float* y;
    const float* dx;
    const float* dy;
    size_t size;

    World() : x(nullptr), y(nullptr), dx(nullptr), dy(nullptr), size(0) {}

    ~World() {
        ALIGNED_FREE(x);
        ALIGNED_FREE(y);
        ALIGNED_FREE((void*)dx);
        ALIGNED_FREE((void*)dy);
    }

    void create_entities(size_t count) {
        constexpr size_t align = 32; // AVX2 32字节对齐

        // 释放旧内存
        ALIGNED_FREE(x);
        ALIGNED_FREE(y);
        ALIGNED_FREE((void*)dx);
        ALIGNED_FREE((void*)dy);

        // 分配对齐内存
        x = static_cast<float*>(ALIGNED_ALLOC(count * sizeof(float), align));
        y = static_cast<float*>(ALIGNED_ALLOC(count * sizeof(float), align));
        dx = static_cast<const float*>(ALIGNED_ALLOC(count * sizeof(float), align));
        dy = static_cast<const float*>(ALIGNED_ALLOC(count * sizeof(float), align));

        // 初始化数据
#pragma omp parallel for
        for (int64_t i = 0; i < count; ++i) {
            x[i] = 0.0f;
            y[i] = 0.0f;
            ((float*)dx)[i] = 1.0f;
            ((float*)dy)[i] = 0.5f;
        }

        size = count;
    }

    __declspec(noinline) void movement_system() noexcept {
        constexpr size_t simd_step = 8; // AVX2每寄存器处理8个float
        const size_t aligned_size = size - (size % simd_step);

        // SIMD向量化处理
        for (size_t i = 0; i < aligned_size; i += simd_step) {
            // 加载数据
            __m256 x_vec = _mm256_load_ps(x + i);
            __m256 dx_vec = _mm256_load_ps(dx + i);
            __m256 y_vec = _mm256_load_ps(y + i);
            __m256 dy_vec = _mm256_load_ps(dy + i);

            // 计算
            x_vec = _mm256_add_ps(x_vec, dx_vec);
            y_vec = _mm256_add_ps(y_vec, dy_vec);

            // 存储结果
            _mm256_store_ps(x + i, x_vec);
            _mm256_store_ps(y + i, y_vec);
        }

        // 处理剩余元素
        for (size_t i = aligned_size; i < size; ++i) {
            x[i] += dx[i];
            y[i] += dy[i];
        }
    }
};

double format_duration(std::chrono::nanoseconds d) {
    return static_cast<double>(d.count()) / 1e6;
}

int main() {
    constexpr size_t ENTITY_COUNT = 10'000'000;
    constexpr size_t ITERATIONS = 100;
    World world;

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
                << format_duration(elapsed) << " ms\n";
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