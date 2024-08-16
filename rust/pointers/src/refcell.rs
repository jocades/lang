use std::cell::UnsafeCell;

use crate::cell::Cell;

// Comply with the borrowing rules.
#[derive(Copy, Clone, Debug)]
enum RefState {
    Unshared,
    Shared(usize), // -> &T
    Exclusive,     // -> &mut T
}

// Implied by UnsafeCell
// impl<T> !Sync for RefCell<T> {}

#[derive(Debug)]
pub struct RefCell<T> {
    value: UnsafeCell<T>,
    state: Cell<RefState>,
}

impl<T> RefCell<T> {
    pub fn new(value: T) -> Self {
        Self {
            value: UnsafeCell::new(value),
            state: Cell::new(RefState::Unshared),
        }
    }

    pub fn borrow(&self) -> Option<Ref<'_, T>> {
        use RefState::*;
        match self.state.get() {
            Unshared => {
                self.state.set(Shared(1));
                Some(Ref { refcell: self })
            }
            Shared(n) => {
                self.state.set(Shared(n + 1));
                Some(Ref { refcell: self })
            }
            Exclusive => None,
        }
    }

    pub fn borrow_mut(&self) -> Option<RefMut<'_, T>> {
        if let RefState::Unshared = self.state.get() {
            self.state.set(RefState::Exclusive);
            Some(RefMut { refcell: self })
        } else {
            None
        }
    }
}

#[derive(Debug)]
struct Ref<'refcell, T> {
    refcell: &'refcell RefCell<T>,
}

impl<T> std::ops::Deref for Ref<'_, T> {
    type Target = T;
    fn deref(&self) -> &Self::Target {
        unsafe { &*self.refcell.value.get() }
    }
}

impl<T> Drop for Ref<'_, T> {
    fn drop(&mut self) {
        use RefState::*;
        match self.refcell.state.get() {
            Exclusive | Unshared => unreachable!(),
            Shared(1) => {
                self.refcell.state.set(Unshared);
            }
            Shared(n) => {
                self.refcell.state.set(Shared(n - 1));
            }
        }
    }
}

struct RefMut<'refcell, T> {
    refcell: &'refcell RefCell<T>,
}

impl<T> std::ops::Deref for RefMut<'_, T> {
    type Target = T;
    fn deref(&self) -> &Self::Target {
        unsafe { &*self.refcell.value.get() }
    }
}

impl<T> std::ops::DerefMut for RefMut<'_, T> {
    fn deref_mut(&mut self) -> &mut Self::Target {
        unsafe { &mut *self.refcell.value.get() }
    }
}

impl<T> Drop for RefMut<'_, T> {
    fn drop(&mut self) {
        use RefState::*;
        match self.refcell.state.get() {
            Shared(_) | Unshared => unreachable!(),
            Exclusive => {
                self.refcell.state.set(Unshared);
            }
        }
    }
}

#[derive(Debug)]
struct User<'a> {
    name: &'a str,
}

impl<'a> User<'_> {
    pub fn greet(&self) {
        println!("Hello I'm {}!", self.name)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn what() {
        let u = RefCell::new(User { name: "Jordi" });
        u.borrow().unwrap().greet();
        u.borrow_mut().unwrap().name = "Other";
        u.borrow().unwrap().greet();
    }
}
