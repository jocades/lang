//! [Lecture by Will Crichton](https://www.youtube.com/watch?v=bnnacleqg6k)

use std::{thread::sleep, time::Duration};

const CLEAR: &str = "\x1B[2J\x1B[1;1H";

struct Progress<I> {
    iter: I,
    i: usize,
}

impl<I> Progress<I> {
    pub fn new(iter: I) -> Self {
        Progress { iter, i: 0 }
    }
}

impl<I> Iterator for Progress<I>
where
    I: Iterator,
{
    type Item = I::Item;

    fn next(&mut self) -> Option<Self::Item> {
        println!("{}{}", CLEAR, "*".repeat(self.i));
        self.i += 1;

        self.iter.next()
    }
}

fn expensive_calculation(_n: &i32) {
    sleep(Duration::from_secs(1));
}

fn main() {
    let v = vec![1, 2, 3];
    for n in Progress::new(v.iter()) {
        expensive_calculation(n);
    }
}
