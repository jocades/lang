use crate::cell::Cell;
use std::{marker::PhantomData, ptr::NonNull};

struct RcInner<T> {
    value: T,
    refcount: Cell<usize>,
}

pub struct Rc<T> {
    inner: NonNull<RcInner<T>>,
    _marker: PhantomData<RcInner<T>>,
}

impl<T> Rc<T> {
    pub fn new(value: T) -> Rc<T> {
        // create a heap allocated pointer
        let inner = Box::new(RcInner {
            value,
            refcount: Cell::new(1),
        });

        Rc {
            // SAFE: a box guarantees heap allocation so this is safe.
            inner: unsafe { NonNull::new_unchecked(Box::into_raw(inner)) }, // convert it into a raw pointer
            _marker: PhantomData,
        }
    }
}

// `.` (dot) operator; struct.prop = (*struct).prop = struct->prop
impl<T> std::ops::Deref for Rc<T> {
    type Target = T;
    fn deref(&self) -> &Self::Target {
        &unsafe { self.inner.as_ref() }.value
    }
}

impl<T> Clone for Rc<T> {
    fn clone(&self) -> Self {
        let inner = unsafe { self.inner.as_ref() }; // -> &*self.inner (create a `ref` from a raw `ptr`)
        let c = inner.refcount.get();
        inner.refcount.set(c + 1);
        Rc {
            inner: self.inner,
            _marker: PhantomData,
        }
    }
}

impl<T> Drop for Rc<T> {
    fn drop(&mut self) {
        let inner = unsafe { self.inner.as_ref() };
        let c = inner.refcount.get();
        if c == 1 {
            // SAFE: we are the _only_ Rc left and we are being dropped.
            // Therefore, after us, there will be no Rc's and no references to T.
            let _ = unsafe { Box::from_raw(self.inner.as_ptr()) };
        } else {
            // Some Rc's still left so dont drop yet.
            inner.refcount.set(c - 1);
        }
    }
}

#[cfg(test)]
mod tests {}
