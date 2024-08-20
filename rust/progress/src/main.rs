//! [Lecture by Will Crichton](https://www.youtube.com/watch?v=bnnacleqg6k)

use std::{thread::sleep, time::Duration};

const CLEAR: &str = "\x1B[2J\x1B[1;1H";

fn progress<I>(iter: I, f: fn(I::Item) -> ())
where
    I: Iterator,
{
    let mut i = 1;
    for n in iter {
        println!("{}{}", CLEAR, "*".repeat(i));
        i += 1;
        // expensive_calculation(n);
        f(n);
    }
}

fn expensive_calculation(_n: &i32) {
    sleep(Duration::from_secs(1));
}

fn main() {
    let v = vec![1, 2, 3];
    progress(v.iter(), expensive_calculation);

    use std::collections::HashSet;
    let mut h = HashSet::new();
    h.insert(0);
    progress(h.iter(), expensive_calculation);
}
