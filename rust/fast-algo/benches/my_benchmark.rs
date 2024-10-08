use criterion::{black_box, criterion_group, criterion_main, BenchmarkId, Criterion};
// use std::fs::File;
use std::time::Duration;

// Import your functions
use fast_algo::{bitwise, reverse, simple, with_array, with_vec, xor};

const TEST: &str = "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw";
const LONGER_TEST: &str = "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjwzcfzfwzzqfrljwzlrfnpqdbhtmscgvjw";

fn criterion_benchmark(c: &mut Criterion) {
    let mut group = c.benchmark_group("string_search");
    group.measurement_time(Duration::from_secs(10));
    group.sample_size(100);

    // let mut wtr = csv::Writer::from_path("benchmark_results.csv").unwrap();
    // wtr.write_record(&["Function", "Input Length", "Median Time (ns)", "MAD (ns)"])
    //     .unwrap();

    for input in [TEST, LONGER_TEST].iter() {
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

            // After each benchmark, write results to CSV
            /* let id = BenchmarkId::new(*name, input_len);
            let estimate = group
                .benchmark_group
                .measurements()
                .get(&id)
                .unwrap()
                .estimates; */
            /* wtr.write_record(&[
                name,
                &input_len.to_string(),
                &estimate.median.to_string(),
                &estimate.mad.to_string(),
            ])
            .unwrap(); */
        }
    }

    group.finish();
    // wtr.flush().unwrap();
}

criterion_group!(benches, criterion_benchmark);
criterion_main!(benches);
