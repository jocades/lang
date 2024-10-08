use criterion::{black_box, criterion_group, criterion_main, BenchmarkId, Criterion};
// use std::fs::File;
use std::time::Duration;

use fast_algo::{bitwise, reverse, simple, with_array, with_vec, xor, PROD, TEST};

fn criterion_benchmark(c: &mut Criterion) {
    let mut group = c.benchmark_group("string_search");
    group.measurement_time(Duration::from_secs(10));
    group.sample_size(100);

    for input in [TEST, PROD].iter() {
        let input_len = input.len();
        for (name, func) in [
            ("simple", simple as fn(&[u8]) -> Option<usize>),
            ("with_vec", with_vec),
            ("with_array", with_array),
            ("bitwise", bitwise),
            ("xor", xor),
            ("reverse", reverse),
        ]
        .iter()
        {
            group.bench_with_input(BenchmarkId::new(*name, input_len), input, |b, i| {
                b.iter(|| func(black_box(i.as_bytes())))
            });
        }
    }

    group.finish();
}

criterion_group!(benches, criterion_benchmark);
criterion_main!(benches);
