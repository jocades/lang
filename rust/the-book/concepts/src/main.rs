mod functions;
mod ownership;

// use functions::fns;
// use ownership::own;

// 5.0 Using Structs to Structure Related Data
fn main() {
    // fns();
    // ownership::own();
    // tuto_structs();

    // using_structs_1();
    // using_structs_2();
    // using_structs_3();
    // using_structs_4();

    // test fold ~= reduce
    using_enums();
    /* let n = vec![1, 2, 3, 4, 5];

    let sum = n.iter().fold(0, |acc, x| acc + x);

    println!("Sum: {}", sum);

    // use string as accumulator
    let words = vec!["hello", "world", "this", "is", "a", "test"];

    let sentence = n.iter().fold(String::new(), |acc, x| acc + " " + x);

    println!("Sentence: {}", sentence); */
}

// 5.1 Defining and Instantiating Structs
#[derive(Debug)]
pub struct User {
    name: String,
    age: i32,
}

impl User {
    fn new(name: String, age: i32) -> User {
        User { name, age }
    }

    fn print(&self) {
        println!("User: {:#?}", self);
    }

    fn is_adult(&self) -> bool {
        self.age >= 18
    }
}

fn tuto_structs() {
    let user = User::new(String::from("Jordi"), 25);
    user.print();
    println!("Is adult: {}", user.is_adult());

    let mut user2 = User { ..user };
    user2.name = String::from("Pepito");
    user2.age = 15;
    user2.print();

    // by copying the values to user2, user values have been moved to user2
    // so we can no longer access them
    // user.print(); // error -> borrow of partially moved value: `user`
}

// 5.2 An Example Program Using Structs
fn using_structs_1() {
    let width1 = 30;
    let height1 = 50;

    println!(
        "The area of the rectangle is {} square pixels.",
        area_1(width1, height1)
    );
}

fn area_1(width: u32, height: u32) -> u32 {
    width * height
}

// Refactoring with Tuples
fn using_structs_2() {
    let rect = (30, 50);

    println!(
        "The area of the rectangle is {} square pixels.",
        area_2(rect)
    );
}

fn area_2(dimensions: (u32, u32)) -> u32 {
    dimensions.0 * dimensions.1
}

// Refactoring with Structs: Adding More Meaning
#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}

fn using_structs_3() {
    let rect = Rectangle {
        width: 30,
        height: 50,
    };

    println!(
        "The area of the rectangle is {} square pixels.",
        area_3(&rect)
    );

    println!("rect is {:#?}", rect);
}

// rectangle: &Rectangle -> inmutable borrow of the struct
fn area_3(rectangle: &Rectangle) -> u32 {
    rectangle.width * rectangle.height
}

// Method Syntax
impl Rectangle {
    fn area(&self) -> u32 {
        self.width * self.height
    }
}

fn using_structs_4() {
    let rect = Rectangle {
        width: 30,
        height: 50,
    };

    println!(
        "The area of the rectangle is {} square pixels.",
        rect.area()
    );
}

#[derive(Debug)]
enum Color {
    Red(u8, u8, u8),
    Green,
    Blue,
}

// can i attach methods to an enum?
impl Color {
    fn print(&self) {
        match self {
            Color::Red(r, g, b) => println!("Red: {r}, {g}, {b}"),
            Color::Green => println!("Green"),
            Color::Blue => println!("Blue"),
        }
    }
}

fn using_enums() {
    let color = Color::Red(255, 0, 0);
    // color.print();

    if let Color::Red(r, g, b) = color {
        println!("Fond red color: {:?} {r} {g} {b}", color);
    }
}

fn closures() {
    let c = |x: &u32| {
        println!("Hello, {}", x);
        x + 1
    };

    let np1 = vec![1, 2, 3, 4, 5].iter().map(c).collect::<Vec<u32>>();
}
