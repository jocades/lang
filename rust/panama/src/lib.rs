//! Flavors:
//! ## Synchronous channels:
//! Channel where send() can block. Limited capacity.
//! - Mutex + Condvar + VecDeque
//! - Atomic VecDeque (atomic queue) + thread::park + thread::Thread::notify
//! ## Asynchronous channels:
//! Channel where send() cannot block. Unbounded.
//! - Mutex + Condvar + VecDeque
//! - Mutex + Condvar + LinkedList
//! - Atomic linked list, linked list of T
//! - Atomic block linked list, linked list of atomic VecDeque<T>
//! ## Rendezvous channels:
//! Synchronous with capacity = 0. Used for thread synchronization.
//! ## Oneshot channels:
//! Any capacity. In practice, only one call to send().

use std::collections::VecDeque;
use std::sync::{Arc, Condvar, Mutex};

#[derive(Debug)]
struct Shared<T> {
    inner: Mutex<Inner<T>>,
    available: Condvar,
}

#[derive(Debug)]
struct Inner<T> {
    queue: VecDeque<T>,
    senders: usize,
}

#[derive(Debug)]
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

#[derive(Debug)]
pub struct Receiver<T> {
    shared: Arc<Shared<T>>,
    buffer: VecDeque<T>,
}

impl<T> Receiver<T> {
    pub fn recv(&mut self) -> Option<T> {
        if let Some(data) = self.buffer.pop_front() {
            return Some(data);
        }

        let mut inner = self.shared.inner.lock().unwrap();
        loop {
            match inner.queue.pop_front() {
                Some(data) => {
                    std::mem::swap(&mut self.buffer, &mut inner.queue);
                    return Some(data);
                }
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
            queue: VecDeque::new(),
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
            buffer: VecDeque::new(),
        },
    )
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::{thread, time::Duration};

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

    #[test]
    fn buffered() {
        let (mut tx, mut rx) = channel();
        tx.send("foo");
        tx.send("bar");
        tx.send("baz");
        dbg!(&tx);
        dbg!(&rx);
        assert_eq!(rx.recv(), Some("foo"));
        dbg!(&tx);
        dbg!(&rx);
        assert_eq!(rx.recv(), Some("bar"));
        assert_eq!(rx.recv(), Some("baz"));
        // let _ = rx.recv(); // This would block waiting for messages
    }

    #[test]
    fn threads() {
        let (mut tx, mut rx) = channel();

        let sender = thread::spawn(move || {
            tx.send("Hello, thread");
        });

        let receiver = thread::spawn(move || {
            let value = rx.recv().expect("Unable to receive from channel");
            assert_eq!(dbg!(value), "Hello, thread");
        });

        sender.join().expect("The sender thread has panicked");
        receiver.join().expect("The receiver thread has panicked");
    }

    #[test]
    fn ref_count() {
        let (tx, mut rx) = channel();
        println!("\nrefs={}", Arc::strong_count(&tx.shared));

        let mut handles = Vec::new();
        for i in 0..10 {
            let mut tx = tx.clone();
            handles.push(thread::spawn(move || {
                tx.send(i);
                println!("refs={} -> {i}", Arc::strong_count(&tx.shared));
            }));
        }

        thread::sleep(Duration::from_millis(100));
        println!("refs={}", Arc::strong_count(&tx.shared));

        for _ in 0..10 {
            let v = rx.recv().unwrap();
            assert!(0 <= v && v < 10);
        }

        // Since we wait to receive exactly 10 messages it kind of acts as a synchronization mechanism
        // So no need to 'wait' for the threads with the handle since recv() is already blocking.
        //
        // for handle in handles {
        //     handle.join().unwrap();
        // }
    }
}
