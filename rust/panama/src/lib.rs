#![allow(unused)]

use std::{
    collections::VecDeque,
    sync::{Arc, Condvar, Mutex},
};

struct Shared<T> {
    inner: Mutex<Inner<T>>,
    available: Condvar,
}

struct Inner<T> {
    queue: VecDeque<T>,
    senders: usize,
}

pub struct Sender<T> {
    shared: Arc<Shared<T>>,
}

impl<T> Clone for Sender<T> {
    fn clone(&self) -> Self {
        let mut inner = self.shared.inner.lock().unwrap();
        inner.senders += 1;
        drop(inner);

        Sender {
            shared: Arc::clone(&self.shared),
        }
    }
}

impl<T> Drop for Sender<T> {
    fn drop(&mut self) {
        let mut inner = self.shared.inner.lock().unwrap();
        inner.senders -= 1;
        let was_last = inner.senders == 0;
        drop(inner);
        if was_last {
            // make sure to wake up the receiever since it may be waiting but there are no active senders
            self.shared.available.notify_one();
        }
    }
}

impl<T> Sender<T> {
    pub fn send(&mut self, data: T) {
        {
            let mut inner = self.shared.inner.lock().unwrap();
            inner.queue.push_back(data);
        } // implicit -> drop(inner);
        self.shared.available.notify_one();
    }
}

pub struct Receiver<T> {
    shared: Arc<Shared<T>>,
}

impl<T> Receiver<T> {
    pub fn recv(&mut self) -> Option<T> {
        let mut inner = self.shared.inner.lock().unwrap();
        loop {
            match inner.queue.pop_front() {
                Some(data) => return Some(data),
                None if inner.senders == 0 => return None,
                None => {
                    inner = self.shared.available.wait(inner).unwrap();
                }
            }
        }
    }
}

/// A cannel for sending and receiving data.
///
/// It returns a tuple containing a [`Sender`] and a [`Receiver`].
///```
/// let (mut tx, mut rx) = panama::channel();
/// tx.send("foo");
/// assert_eq!(rx.recv(), Some("foo"));
///```
pub fn channel<T>() -> (Sender<T>, Receiver<T>) {
    let shared = Arc::new(Shared {
        inner: Mutex::new(Inner {
            queue: VecDeque::default(),
            senders: 1,
        }),
        available: Condvar::new(),
    });

    (
        Sender {
            shared: Arc::clone(&shared),
        },
        Receiver {
            shared: Arc::clone(&shared),
        },
    )
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn ping_pong() {
        let (mut tx, mut rx) = channel();
        tx.send("foo");
        assert_eq!(rx.recv(), Some("foo"));
    }

    #[test]
    fn closed_tx() {
        let (tx, mut rx) = channel::<&str>();
        drop(tx);
        assert_eq!(rx.recv(), None);
    }

    #[test]
    fn closed_rx() {
        let (mut tx, rx) = channel::<&str>();
        drop(rx);
        tx.send("foo"); // what happens when we try to send but there are no receivers is more of a
                        // design choice, in some cases we might want to error and take some action
                        // but in this case we just send into the void
    }
}