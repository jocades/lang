#![allow(dead_code)]

use std::{cell::UnsafeCell, sync::atomic::AtomicBool};

const LOCKED: bool = true;
const UNLOCKED: bool = false;

struct Mutex<T> {
    locked: AtomicBool,
    inner: UnsafeCell<T>,
}

impl<T> Mutex<T> {
    fn new(inner: T) -> Self {
        Self {
            locked: AtomicBool::new(UNLOCKED),
            inner: UnsafeCell::new(inner),
        }
    }

    fn with_lock<R>(f: impl FnOnce(&mut T) -> R) -> R {
        todo!()
    }
}

fn main() {
    println!("Hello, world!");
}
