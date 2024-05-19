pub fn fns() {
    let x = 5;
    let y = {
        let x = 3;
        x + 1
    };
    // println!("The value of x is: {}", x);
    println!("The value of y is: {}", y);

    another_function(x);

    println!("The value of five is: {}", five());

    let z = add(5, 3);

    println!("The value of z is: {}", z);

    let ls = [1, 2, 3, 4, 5];

    for n in ls {
        println!("The value of n is: {}", n);
    }

    for n in (1..4).rev() {
        println!("The value of n is: {}", n);
    }
}

fn another_function(x: i32) {
    println!("The value of x is: {x}");
}

// Returning values from functions in Rust is easy. Just don't put a semicolon at the end of the expression.
// The last expression in the function will be returned.
// Or you can use the return keyword but with a semicolon.
fn five() -> i32 {
    5 // same as: return 5;
}

fn add(x: i32, y: i32) -> i32 {
    x + y
}
