// main.cpp
#include <vector>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <memory>
#include <cassert>

// ��ȫƥ��Rust��#[repr(C)]�ڴ沼��
//#pragma pack(push, 1)
struct Position {
    float x;
    float y;
};
struct Velocity {
    float dx;
    float dy;
};
//#pragma pack(pop)

class World {
    std::vector<Position> positions;
    std::vector<Velocity> velocities;

public:
    void create_entities(size_t count) {
        positions.clear();
        velocities.clear();

        positions.reserve(count);
        velocities.reserve(count);

        // ������ʼ�����������push_back�Ŀ�����
        const Position default_pos{ 0.0f, 0.0f };
        const Velocity default_vel{ 1.0f, 0.5f };
        positions.assign(count, default_pos);
        velocities.assign(count, default_vel);
    }

    __declspec(noinline) void movement_system() noexcept {
        // ȷ���ڴ���루MSVC��Ҫ�˶��ԣ�
        assert(reinterpret_cast<uintptr_t>(positions.data()) % 16 == 0);
        assert(reinterpret_cast<uintptr_t>(velocities.data()) % 16 == 0);

        // ��ѭ������ȫ�����������Զ���������
        const size_t size = positions.size();
        Position* __restrict p_pos = positions.data();
        const Velocity* __restrict p_vel = velocities.data();

//#pragma loop(ivdep) // ���������������
        for (size_t i = 0; i < size; ++i) {
            p_pos[i].x += p_vel[i].dx;
            p_pos[i].y += p_vel[i].dy;
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

    // ʵ�崴����ʱ
    auto create_start = std::chrono::high_resolution_clock::now();
    world.create_entities(ENTITY_COUNT);
    auto create_time = std::chrono::high_resolution_clock::now() - create_start;
    std::cout << "Entities created in "
        << std::chrono::duration_cast<std::chrono::microseconds>(create_time).count()
        << " ��s\n";

    // Ԥ�����У���Rust�汾��ȫһ�£�
    for (int i = 0; i < 5; ++i) {
        world.movement_system();
    }

    // ��׼����
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

    // ͳ�ƽ��
    const double avg_time = total_time.count() / static_cast<double>(ITERATIONS);
    const double per_entity = avg_time / ENTITY_COUNT;
    const double throughput = ENTITY_COUNT / (avg_time / 1e9) / 1e6;

    std::cout << "\nAverage per entity: " << std::fixed << std::setprecision(6)
        << per_entity << " ns/entity\n";
    std::cout << "Throughput: " << std::fixed << std::setprecision(2)
        << throughput << " M entities/sec\n";

    return 0;
}