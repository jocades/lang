use std::fmt;
// LINKED LIST

// Define a structure which will represent a node of the linked list
#[derive(Debug)]
struct Node {
    value: i32,
    next: Option<Box<Node>>,
}

// Implement the Display trait for the Node structure
impl fmt::Display for Node {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Node: {}", self.value)
    }
}

// Define a structure which will represent the linked list
struct LinkedList {
    head: Option<Box<Node>>,
}

// Implement the Display trait for the LinkedList structure
impl fmt::Display for LinkedList {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let mut current = &self.head;
        write!(f, "LinkedList: [")?;
        loop {
            match current {
                Some(node) => {
                    write!(f, "{}", node)?;
                    current = &node.next;
                    if current.is_some() {
                        write!(f, ", ")?;
                    }
                }
                None => break,
            }
        }
        write!(f, "]")
    }
}

// Implement the LinkedList structure
impl LinkedList {
    // Create a new linked list
    fn new() -> LinkedList {
        LinkedList { head: None }
    }

    // Add a new node to the linked list
    fn push(&mut self, value: i32) {
        let new_node = Node {
            value,
            next: self.head.take(),
        };
        self.head = Some(Box::new(new_node));
    }

    // Remove the first node from the linked list
    fn pop(&mut self) -> Option<i32> {
        self.head.take().map(|node| {
            self.head = node.next;
            node.value
        })
    }

    // get at index
    fn get(&self, index: i32) -> Option<i32> {
        let mut current = &self.head;
        let mut i = 0;
        loop {
            match current {
                Some(node) => {
                    if i == index {
                        return Some(node.value);
                    }
                    current = &node.next;
                    i += 1;
                }
                None => break,
            }
        }
        None
    }

    fn set(&mut self, index: i32, value: i32) {
        let mut current = &mut self.head;
        let mut i = 0;
        loop {
            match current {
                Some(node) => {
                    if i == index {
                        node.value = value;
                        return;
                    }
                    current = &mut node.next;
                    i += 1;
                }
                None => break,
            }
        }
    }
}

pub fn ll() {
    // Create a new linked list
    let mut list = LinkedList::new();

    // Add some nodes to the linked list
    list.push(1);
    list.push(2);
    list.push(3);

    // Print the linked list
    println!("{}", list);

    // Remove the first node from the linked list
    let value = list.pop();
    println!("Popped value: {:?}", value);

    // Print the linked list
    println!("{}", list);

    for i in 3..=5 {
        list.push(i);
    }

    println!("{}", list);

    // Get the value at index 2
    let value = list.get(2);
    println!("Value at index 2: {:?}", value);

    // Set the value at index 2
    list.set(2, 10);
    println!("{}", list);
}
