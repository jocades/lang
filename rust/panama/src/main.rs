#![allow(unused)]

use std::sync::{Arc, Mutex};

struct Sender<T> {
    inner: Arc<Mutex<Inner<T>>>,
}

struct Receiver<T> {
    inner: Arc<Mutex<Inner<T>>>,
}

struct Inner<T> {
    queue: Vec<T>,
}

fn channel<T>() -> (Sender<T>, Receiver<T>) {
    let inner = Arc::new(Mutex::new(Inner { queue: Vec::new() }));
    (
        Sender {
            inner: Arc::clone(&inner),
        },
        Receiver {
            inner: Arc::clone(&inner),
        },
    )
}

fn main() {
    let (tx, rx) = channel::<u8>();
}
