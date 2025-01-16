use std::{marker::PhantomData, ptr::NonNull};

pub trait Speak {
    fn speak(&self);
}

pub struct Cat;
impl Speak for Cat {
    fn speak(&self) {
        println!("meow");
    }
}

pub struct Dog;
impl Speak for Dog {
    fn speak(&self) {
        println!("woof");
    }
}

pub struct AnythingSpeak<'a> {
    _marker: PhantomData<&'a ()>,
    data: NonNull<()>,
    speak_thunk: unsafe fn(NonNull<()>),
}

impl<'a> AnythingSpeak<'a> {
    pub fn new<T: Speak>(t: &'a T) -> Self {
        Self {
            _marker: PhantomData,
            data: NonNull::from(t).cast(),
            speak_thunk: |data| unsafe { data.cast::<T>().as_ref() }.speak(),
        }
    }

    pub fn speak(&self) {
        unsafe { (self.speak_thunk)(self.data) }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let mut a = AnythingSpeak::new(&Cat);
        a.speak();
        a = AnythingSpeak::new(&Dog);
        a.speak();
    }
}
