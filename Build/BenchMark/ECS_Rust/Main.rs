use std::time::{Instant, Duration};

#[repr(C)]
#[derive(Clone)]
struct Position {
    x: f32,
    y: f32,
}

#[repr(C)]
#[derive(Clone)]
struct Velocity {
    dx: f32,
    dy: f32,
}

struct World {
    positions: Vec<Position>,
    velocities: Vec<Velocity>,
}

impl World {
    fn new() -> Self {
        World {
            positions: Vec::new(),
            velocities: Vec::new(),
        }
    }

    fn create_entities(&mut self, count: usize) {
        self.positions = vec![Position { x: 0.0, y: 0.0 }; count];
        self.velocities = vec![Velocity { dx: 1.0, dy: 0.5 }; count];
    }

    #[inline(never)]
    fn movement_system(&mut self) {
        self.positions
            .iter_mut()
            .zip(self.velocities.iter())
            .for_each(|(pos, vel)| {
                pos.x += vel.dx;
                pos.y += vel.dy;
            });
    }
}

fn format_duration(d: Duration) -> String {
    let nanos = d.as_nanos() as f64;
    format!("{:.4}", nanos / 1e6) // 转换为毫秒保留4位小数
}

fn main() {
    const ENTITY_COUNT: usize = 10_000_000;
    const ITERATIONS: usize = 100;
    let mut world = World::new();

    // 实体创建计时
    let create_start = Instant::now();
    world.create_entities(ENTITY_COUNT);
    let create_time = create_start.elapsed();
    println!("Entities created in {} μs", create_time.as_micros());

    // 预热运行（与C++版本一致）
    for _ in 0..5 {
        world.movement_system();
    }

    // 基准测试
    let mut total_time = Duration::ZERO;
    for i in 0..ITERATIONS {
        let start = Instant::now();
        world.movement_system();
        let elapsed = start.elapsed();
        total_time += elapsed;

        // 每10次输出中间结果（毫秒单位）
        if (i + 1) % 10 == 0 {
            println!("Iteration {}: {} ms", 
                i + 1, 
                format_duration(elapsed)
            );
        }
    }

    // 统计结果（与C++相同计算公式）
    let avg_time = total_time.as_nanos() as f64 / ITERATIONS as f64;
    let per_entity = avg_time / ENTITY_COUNT as f64;
    let throughput = ENTITY_COUNT as f64 / (avg_time / 1e9) / 1e6;

    println!("\nAverage per entity: {:.6} ns/entity", per_entity);
    println!("Throughput: {:.2} M entities/sec", throughput);
}