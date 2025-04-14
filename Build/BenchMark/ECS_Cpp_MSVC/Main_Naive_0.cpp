#include <iostream>
#include <vector>
#include <chrono>

struct Position {
    float x;
    float y;

    Position(float x = 0, float y = 0) : x(x), y(y) {}
};

struct Velocity {
    float dx;
    float dy;

    Velocity(float dx = 0, float dy = 0) : dx(dx), dy(dy) {}
};

class World {
private:
    std::vector<Position> positions;
    std::vector<Velocity> velocities;

public:
    // 创建实体并初始化组件
    void create_entities(size_t count) {
        positions.clear();
        velocities.clear();

        positions.reserve(count);
        velocities.reserve(count);

        // 初始化组件数据（与 Rust 的 vec! 初始化逻辑一致）
        for (size_t i = 0; i < count; ++i) {
            positions.emplace_back(0.0f, 0.0f);
            velocities.emplace_back(1.0f, 0.5f);
        }
    }

    // 移动系统（与 Rust 相同的算法逻辑）
    // 禁止内联以匹配 Rust 的 #[inline(never)]
        void movement_system() {
        const size_t size = positions.size();
        Position* pos_data = positions.data();
        const Velocity* vel_data = velocities.data();

        // 手动循环展开 + 向量化提示
        for (size_t i = 0; i < size; ++i) {
            pos_data[i].x += vel_data[i].dx;
            pos_data[i].y += vel_data[i].dy;
        }
    }
};

int main() {
    const size_t ENTITY_COUNT = 10'000'000;
    const size_t ITERATIONS = 100;
    World world;

    // 创建实体并计时
    auto start_create = std::chrono::high_resolution_clock::now();
    world.create_entities(ENTITY_COUNT);
    auto create_duration = std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::high_resolution_clock::now() - start_create
    );
    std::cout << "Entities created in " << create_duration.count() << " μs\n";

    // 预热运行
    for (int i = 0; i < 5; ++i) {
        world.movement_system();
    }

    // 基准测试
    double total_time = 0.0;
    for (size_t i = 0; i < ITERATIONS; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        world.movement_system();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now() - start
        ).count();

        total_time += duration / 1e9;

        if ((i + 1) % 10 == 0) {
            std::cout << "Iteration " << (i + 1)
                << ": " << (duration / 1e6) << " ms\n";
        }
    }

    // 输出结果
    const double avg_time = total_time / ITERATIONS;
    std::cout << "\nAverage per entity: "
        << (avg_time * 1e9) / ENTITY_COUNT << " ns/entity\n";
    std::cout << "Throughput: "
        << ENTITY_COUNT / avg_time / 1e6 << " M entities/sec\n";

    return 0;
}