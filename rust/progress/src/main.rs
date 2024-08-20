//! [Lecture by Will Crichton](https://www.youtube.com/watch?v=bnnacleqg6k)

use std::{thread::sleep, time::Duration};

const CLEAR: &str = "\x1B[2J\x1B[1;1H";

// type state
struct Unbounded;
struct Bounded {
    bound: usize,
    delims: (char, char),
}

struct Progress<I, B> {
    iter: I,
    bound: B,
    i: usize,
}

trait ProgressDisplay: Sized {
    fn display<I>(&self, progress: &Progress<I, Self>);
}

impl ProgressDisplay for Unbounded {
    fn display<I>(&self, progress: &Progress<I, Self>) {
        println!("{}", "*".repeat(progress.i));
    }
}

impl ProgressDisplay for Bounded {
    fn display<I>(&self, progress: &Progress<I, Self>) {
        println!(
            "{}{}{}{}",
            self.delims.0,
            "*".repeat(progress.i),
            " ".repeat(self.bound - progress.i),
            self.delims.1
        );
    }
}

impl<I> Progress<I, Unbounded> {
    pub fn new(iter: I) -> Self {
        Progress {
            iter,
            i: 0,
            bound: Unbounded,
        }
    }
}

// Only draw bounds when the iterator has bounds
impl<I: ExactSizeIterator> Progress<I, Unbounded> {
    // this will change the type of the Progress struct (that is the key of type state)
    pub fn with_bound(self) -> Progress<I, Bounded> {
        let bound = Bounded {
            bound: self.iter.len(),
            delims: ('[', ']'),
        };

        Progress {
            i: self.i,
            iter: self.iter,
            bound,
        }
    }
}

impl<I> Progress<I, Bounded> {
    pub fn with_delims(mut self, delims: (char, char)) -> Self {
        self.bound.delims = delims;
        self
    }
}

impl<I, B> Iterator for Progress<I, B>
where
    I: Iterator,
    B: ProgressDisplay,
{
    type Item = I::Item;

    fn next(&mut self) -> Option<Self::Item> {
        print!("{CLEAR}");
        self.bound.display(&self);
        self.i += 1;
        self.iter.next()
    }
}

trait ProgressIteratorExt: Sized {
    fn progress(self) -> Progress<Self, Unbounded>;
}

impl<I: Iterator> ProgressIteratorExt for I {
    fn progress(self) -> Progress<I, Unbounded> {
        Progress::new(self)
    }
}

fn expensive_calculation(_n: &i32) {
    sleep(Duration::from_secs(1));
}

fn main() {
    let v = vec![1, 2, 3];

    for n in v.iter().progress().with_bound() {
        expensive_calculation(n);
    }

    let delims = ('<', '>');
    for n in v.iter().progress().with_bound().with_delims(delims) {
        expensive_calculation(n);
    }

    // no method that requires a bounded iterable is allowed here,
    // since we enconded the state in the type system.
    /* for n in (0..).progress() {
        expensive_calculation(&n);
    } */
}
