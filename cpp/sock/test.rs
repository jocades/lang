use std::thread;

const NUM_THREADS: usize = 8;
const INC: usize = 1000;

static mut COUNTER: usize = 0;

fn main() {
    let tasks = (0..NUM_THREADS)
        .map(|_| {
            thread::spawn(|| {
                for _ in 0..INC {
                    unsafe {
                        COUNTER += 1;
                    }
                }
            })
        })
        .collect::<Vec<_>>();

    for task in tasks {
        _ = task.join();
    }

    unsafe {
        println!("{COUNTER}");
        assert_eq!(COUNTER, NUM_THREADS * INC);
    }
}
