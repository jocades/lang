use std::alloc::{self, Layout};
use std::mem::ManuallyDrop;
use std::ops::{Deref, DerefMut};
use std::ptr::NonNull;
use std::{mem, ptr};

#[derive(Debug)]
struct RawVec<T> {
    ptr: NonNull<T>,
    cap: usize,
}

unsafe impl<T: Send> Send for RawVec<T> {}
unsafe impl<T: Sync> Sync for RawVec<T> {}

impl<T> RawVec<T> {
    pub fn new() -> Self {
        assert!(mem::size_of::<T>() != 0, "TODO: implement ZST support");
        RawVec {
            ptr: NonNull::dangling(),
            cap: 0,
        }
    }

    fn grow(&mut self) {
        // This can't overflow because we ensure self.cap <= isize::MAX.
        let new_cap = if self.cap == 0 { 1 } else { 2 * self.cap };

        // Layout::array checks that the number of bytes is <= usize::MAX,
        // but this is redundant since old_layout.size() <= isize::MAX,
        // so the `unwrap` should never fail.
        let new_layout = Layout::array::<T>(new_cap).unwrap();

        // Ensure that the new allocation doesn't exceed `isize::MAX` bytes.
        assert!(
            new_layout.size() <= isize::MAX as usize,
            "Allocation too large"
        );

        let new_ptr = if self.cap == 0 {
            unsafe { alloc::alloc(new_layout) }
        } else {
            let old_layout = Layout::array::<T>(self.cap).unwrap();
            let old_ptr = self.ptr.as_ptr() as *mut u8;
            unsafe { alloc::realloc(old_ptr, old_layout, new_layout.size()) }
        };

        // If allocation fails, `new_ptr` will be null, in which case we abort.
        self.ptr = match NonNull::new(new_ptr as *mut T) {
            Some(p) => p,
            None => alloc::handle_alloc_error(new_layout),
        };
        self.cap = new_cap;
    }
}

impl<T> Drop for RawVec<T> {
    fn drop(&mut self) {
        if self.cap != 0 {
            let layout = Layout::array::<T>(self.cap).unwrap();
            unsafe {
                alloc::dealloc(self.ptr.as_ptr() as *mut u8, layout);
            }
        }
    }
}

#[derive(Debug)]
pub struct Vec<T> {
    buf: RawVec<T>,
    len: usize,
}

impl<T> Vec<T> {
    fn ptr(&self) -> *mut T {
        self.buf.ptr.as_ptr()
    }

    fn cap(&self) -> usize {
        self.buf.cap
    }

    fn grow(&mut self) {
        self.buf.grow();
    }

    pub fn new() -> Self {
        Vec {
            buf: RawVec::new(),
            len: 0,
        }
    }

    pub fn push(&mut self, item: T) {
        if self.len == self.cap() {
            self.grow();
        }

        unsafe { ptr::write(self.ptr().add(self.len), item) };

        // Can't fail, we will OOM first.
        self.len += 1;
    }

    pub fn pop(&mut self) -> Option<T> {
        if self.len == 0 {
            None
        } else {
            self.len -= 1;
            unsafe { Some(ptr::read(self.ptr().add(self.len))) }
        }
    }

    pub fn insert(&mut self, index: usize, item: T) {
        // Note: `<=` because it is valid to insert after everything
        // which would be equivalent to push.
        assert!(index <= self.len, "index out of bound");
        if self.len == self.cap() {
            self.grow();
        }

        unsafe {
            // ptr::copy(src, dest, len): "copy from source to dest len elements"
            ptr::copy(
                self.ptr().add(index),
                self.ptr().add(index + 1),
                self.len - index,
            );
            ptr::write(self.ptr().add(index), item)
        }

        self.len += 1;
    }

    pub fn remove(&mut self, index: usize) -> T {
        // Note: `<` because it is _not_ valid to remove after everything.
        assert!(index < self.len, "index out of bounds");
        unsafe {
            self.len -= 1;
            let result = ptr::read(self.ptr().add(index));
            ptr::copy(
                self.ptr().add(index + 1),
                self.ptr().add(index),
                self.len - index,
            );
            result
        }
    }
}

impl<T> Drop for Vec<T> {
    fn drop(&mut self) {
        while let Some(_) = self.pop() {}
        // deallocation is handled by `RawVec`
    }
}

impl<T> Deref for Vec<T> {
    type Target = [T];
    fn deref(&self) -> &Self::Target {
        unsafe { std::slice::from_raw_parts(self.ptr(), self.len) }
    }
}

impl<T> DerefMut for Vec<T> {
    fn deref_mut(&mut self) -> &mut Self::Target {
        unsafe { std::slice::from_raw_parts_mut(self.ptr(), self.len) }
    }
}

// `iter` and `iter_mut` have already been written for us thanks to The Magic of Deref.

// `IntoIter` consumes the Vec by-value, and can consequently yield its elements by-value.
// In order to enable this, IntoIter needs to take control of Vec's allocation.
#[derive(Debug)]
pub struct IntoIter<T> {
    _buf: RawVec<T>, // we don't actually care about this. Just need it to live.
    start: *const T,
    end: *const T,
}

impl<T> IntoIterator for Vec<T> {
    type Item = T;
    type IntoIter = IntoIter<T>;
    fn into_iter(self) -> Self::IntoIter {
        // need to use ptr::read to unsafely move the buf out since it's
        // not Copy, and Vec implements Drop (so we can't destructure it).
        let buf = unsafe { ptr::read(&self.buf) };
        let len = self.len;
        mem::forget(self);

        IntoIter {
            start: buf.ptr.as_ptr(),
            end: if buf.cap == 0 {
                // cannot offset off a pointer unless it is part of an allocation
                buf.ptr.as_ptr()
            } else {
                unsafe { buf.ptr.as_ptr().add(len) }
            },
            _buf: buf,
        }
    }
}

impl<T> Iterator for IntoIter<T> {
    type Item = T;
    fn next(&mut self) -> Option<Self::Item> {
        if self.start == self.end {
            None
        } else {
            unsafe {
                let result = ptr::read(self.start);
                self.start = self.start.offset(1);
                Some(result)
            }
        }
    }

    fn size_hint(&self) -> (usize, Option<usize>) {
        let len = (self.end as usize - self.start as usize) / mem::size_of::<T>();
        (len, Some(len))
    }
}

// Iterating backwards
impl<T> DoubleEndedIterator for IntoIter<T> {
    fn next_back(&mut self) -> Option<Self::Item> {
        if self.start == self.end {
            None
        } else {
            unsafe {
                self.end = self.end.offset(-1);
                Some(ptr::read(self.end))
            }
        }
    }
}

// Because IntoIter takes ownership of its allocation, it needs to implement Drop to free it.
// However it also wants to implement Drop to drop any elements it contains that weren't yielded.
impl<T> Drop for IntoIter<T> {
    fn drop(&mut self) {
        // only need to ensure all out elements are read;
        // buffer will clean itself up afterwards.
        for _ in &mut *self {}
    }
}

fn coerce(v: &[i32]) -> usize {
    v.len()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_vec() {
        let mut v = Vec::new();
        for i in 0..4 {
            v.push(i)
        }
        println!("Grow exact: {v:?}");
        v.push(5); // len == cap -> cap = 2 * cap
        println!("Grow oversize: {v:?}");

        // The `.` derefs automagically so we can use all the methods from a slice `&[T]`;
        v.iter_mut().for_each(|n| *n = *n * 2);

        // The power of deref:
        let len = coerce(&v);
    }

    fn sized(n: u32) -> Vec<u32> {
        let mut v = Vec::new();
        for i in 0..n {
            v.push(i)
        }
        v
    }

    #[test]
    fn test_into_iter() {
        let v = sized(10);
        let mut iter = v.into_iter();
        let first = iter.next();
        println!("{first:?}");
        drop(iter); // the rest of non_consumed elements are dropped
    }
}
