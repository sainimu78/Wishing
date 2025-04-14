#include <vector>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <cassert>

struct Position {
    float x;
    float y;
};
struct Velocity {
    float dx;
    float dy;
};

class World {
    std::vector<Position> positions;
    std::vector<Velocity> velocities;

public:
    void create_entities(size_t count) {
        positions.clear();
        velocities.clear();

        // 批量初始化保持内存连续性
        positions.resize(count, Position{0.0f, 0.0f});
        velocities.resize(count, Velocity{1.0f, 0.5f});

        // 内存对齐验证
        assert(reinterpret_cast<uintptr_t>(positions.data()) % 32 == 0);
        assert(reinterpret_cast<uintptr_t>(velocities.data()) % 32 == 0);
    }

	void movement_system() noexcept {
        const size_t size = positions.size();
        Position* pos = positions.data();
        const Velocity* vel = velocities.data();

        for (size_t i = 0; i < size; ++i) {
            pos[i].x += vel[i].dx;
            pos[i].y += vel[i].dy;
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
              << " us\n";

    // 预热运行（与 Rust 完全一致）
    for (int i = 0; i < 5; ++i) {
        world.movement_system();
    }

    // 基准测试
    std::chrono::nanoseconds total_time{0};
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