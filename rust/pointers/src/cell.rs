#![allow(unused)]

use std::cell::UnsafeCell;

pub struct Cell<T> {
    value: UnsafeCell<T>,
}

// Implied by unsafe cell
// impl<T> !Sync for Cell<T> {}
unsafe impl<T> Sync for Cell<T> {}

impl<T> Cell<T> {
    pub fn new(value: T) -> Self {
        Cell {
            value: UnsafeCell::new(value),
        }
    }

    pub fn set(&self, value: T) {
        unsafe { *self.value.get() = value };
    }

    pub fn get(&self) -> &T {
        unsafe { &*self.value.get() }
    }
}

#[cfg(test)]
mod tests {
    use super::Cell;
    use std::sync::Arc;

    #[test]
    fn bad() {
        let x = Arc::new(Cell::new(42));

        let x1 = Arc::clone(&x);
        std::thread::spawn(move || {
            x1.set(43);
        });

        let x2 = Arc::clone(&x);
        std::thread::spawn(move || {
            x2.set(44);
        });
    }

    #[test]
    fn bad2() {
        let x = Cell::new(String::from("hello"));
        let first = x.get();
        x.set(String::from("bye"));
        println!("--> {}", first);
    }
}
