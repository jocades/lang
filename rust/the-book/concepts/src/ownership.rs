pub fn own() {
    // let ref_to_nothing = dangle();
    // println!("{}", ref_to_nothing);

    let mut s = String::from("hello world");
    let word_size = first_word_size(&s);
    println!("Word size: {word_size}");

    let word = first_word(&s);
    println!("First word: {}", word);

    let (hello, world) = slice_strings(&s);

    println!("slice_string: {} {}", hello, world);

    s.clear(); // this empties the String, making it equal to ""
    println!("Now the string is: {}", s);

    struct_own();
}

// taking the reference of a string so that we do not have ownership of the string
fn first_word_size(s: &String) -> usize {
    let bytes = s.as_bytes();
    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return i;
        }
    }
    s.len()
}

fn first_word(s: &String) -> &str {
    for (i, &item) in s.as_bytes().iter().enumerate() {
        if item == b' ' {
            return &s[..i];
        }
    }
    &s[..]
}

// -> ("hello", "world")
fn slice_strings(s: &String) -> (&str, &str) {
    let mut first_space = 0;
    for (i, &item) in s.as_bytes().iter().enumerate() {
        if item == b' ' {
            first_space = i;
            break;
        }
    }
    // let first = &s[0..first_space];
    // let second = &s[first_space + 1..s.len()];
    // or we can avoid adding the first and last indexes in the range slice since they are the default
    let first = &s[..first_space];
    let second = &s[first_space + 1..];
    (first, second)
}

/* fn dangle() -> &String {
    let s = String::new();
    &s
} */

#[derive(Debug)]
struct Point {
    x: i32,
    y: i32,
}

impl Point {
    fn origin() -> Point {
        Point { x: 0, y: 0 }
    }
}

#[derive(Debug)]
struct Line {
    start: Point,
    end: Point,
}

impl Line {
    fn new(mut start: Point, end: Point) -> Line {
        start.x = 5;
        start.y = 5;
        Line { start, end }
    }
}

fn struct_own() {
    let p1 = Point::origin();
    let p2 = p1;
    // println!("p1: {}", p1.x); // error: value borrowed here after move
    println!("p2: {}", p2.x);

    read_only(&p2);

    let mut p3 = p2;
    read_write(&mut p3);
    println!("now p3.x is: {}", p3.x);

    let p4 = p3;
    move_ownership(p4);
    // println!("p4.x is: {}", p4.x); // error: value borrowed here after move

    let l1 = Line::new(Point::origin(), Point { x: 10, y: 10 });
    println!("Line: {:#?}", l1);
    let start_x = l1.start;
    println!("Line start.x: {:#?}", start_x);
    // println!("Line start.x: {:#?}", l1.start.x); // error -> value moved to _start_x
}

fn read_only(p: &Point) {
    // p.x = 10; // error: cannot assign to `p.x` because it is borrowed
    println!("Read only: {}", p.x);
}

fn read_write(p: &mut Point) {
    p.x = 10;
    println!("Read write: {}", p.x);
}

fn move_ownership(mut p: Point) {
    p.x = 20;
    println!("Move ownership: {}", p.x);
}
