use std::cell::UnsafeCell;

#[derive(Debug)]
pub struct Cell<T> {
    value: UnsafeCell<T>,
}

// Implied by UnsafeCell
// impl<T> !Sync for Cell<T> {}

impl<T> Cell<T> {
    pub fn new(value: T) -> Self {
        Cell {
            value: UnsafeCell::new(value),
        }
    }

    pub fn set(&self, value: T) {
        // SAFETY: we know no-one else is cuncurrently mutating self.value (becuase !Sync)
        // SAFETY: we know we are not invalidating any references, because we never give any out.
        unsafe { *self.value.get() = value };
    }

    pub fn get(&self) -> T
    where
        T: Copy,
    {
        // SAFETY: we know no-one else is modifying this value, since only this
        // thread can mutate (becuase !Sync), and it is executing this function instead.
        unsafe { *self.value.get() }
    }
}

#[cfg(test)]
mod tests {
    use super::Cell;
    use std::sync::Arc;

    #[test]
    fn bad() {
        /* let x = Arc::new(Cell::new(42));

        let x1 = Arc::clone(&x);
        let jh1 = std::thread::spawn(move || {
            for _ in 0..100_000 {
                let x = x1.get();
                x1.set(x + 1);
            }
        });

        let x2 = Arc::clone(&x);
        let jh2 = std::thread::spawn(move || {
            for _ in 0..100_000 {
                let x = x2.get();
                x2.set(x + 1);
            }
        });

        jh2.join().unwrap();
        jh1.join().unwrap();
        assert_eq!(x.get(), 200_000); */
    }
}
