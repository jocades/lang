use std::fmt;
use std::fs;
use std::fs::{File, OpenOptions};
use std::io;
use std::io::prelude::*;
#[cfg(target_family = "unix")]
use std::os::unix;
#[cfg(target_family = "windows")]
use std::os::windows;
use std::path::Path;

mod ll;
mod vectors;

use ll::ll;

fn main() {
    // test_path();
    // test_file_io();
    // test_result();
    // test_option();
    // ll();
    vectors::test();
    // let x = 5;
    // let y = &x;
    // assert_eq!(5, x);
    // assert_eq!(5, *y);
    // // how to print the mem adress and size of a variable
    // println!("x is {:p} and is {} bytes", &x, std::mem::size_of_val(&x));
    // println!("y is {:p} and is {} bytes", y, std::mem::size_of_val(y));
}

fn test_path() {
    let path = Path::new("./src");
    let display = path.display();

    let mut new_path = path.join("a").join("b");

    new_path.push("set.txt");
    new_path.set_file_name("test.txt");

    match new_path.to_str() {
        None => panic!("new path is not a valid UTF-8 sequence"),
        Some(s) => println!("new path is {}", s),
    }

    // iter directory
    walk(path).unwrap();
}

// recursively walk the directory
fn walk(path: &Path) -> io::Result<()> {
    if path.is_dir() {
        for entry in fs::read_dir(path)? {
            let path = entry?.path();
            if path.is_dir() {
                walk(&path)?;
            } else {
                println!("{:?}", path);
            }
        }
    }
    Ok(())
}

static LOREM_IPSUM: &str =
    "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod
tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam,
quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo
consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse
cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non
proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
";

fn test_file_io() {
    // READ
    // Create a path to the desired file
    let path = Path::new("hello.txt");
    let display = path.display();

    // Open the path in read-only mode, returns `io::Result<File>`
    let mut file = match File::open(&path) {
        Err(why) => panic!("couldn't open {}: {}", display, why),
        Ok(file) => file,
    };

    // Read the file contents into a string, returns `io::Result<usize>`
    let mut s = String::new();
    match file.read_to_string(&mut s) {
        Err(why) => panic!("couldn't read {}: {}", display, why),
        Ok(_) => print!("{} contains:\n{}", display, s),
    }

    // WRITE
    let path = Path::new("lorem_ipsum.txt");
    let display = path.display();

    // Open a file in write-only mode, returns `io::Result<File>`
    let mut file = match File::create(&path) {
        Err(why) => panic!("couldn't create {}: {}", display, why),
        Ok(file) => file,
    };

    // Write the `LOREM_IPSUM` string to `file`, returns `io::Result<()>`
    match file.write_all(LOREM_IPSUM.as_bytes()) {
        Err(why) => panic!("couldn't write to {}: {}", display, why),
        Ok(_) => println!("successfully wrote to {}", display),
    }
}

// resting RESULT type
// and error handling
fn test_result() {
    // craeting a result type
    let result: Result<i32, &str> = Ok(200);
    println!("Result is {:#?}", result);
    // let result: Result<i32, &str> = Err("Some error message");

    // using the result type to handle errors
    match result {
        Ok(value) => println!("Result is {}", value),
        Err(err) => println!("Error is {}", err),
    }

    // using unwrap to handle errors
    // unwrap will return the value if the result is Ok
    // otherwise it will panic with the error message
    let value = result.unwrap();
    println!("Value is {}", value);

    // using expect to handle errors
    // expect will return the value if the result is Ok
    // otherwise it will panic with the error message
    let value = result.expect("Some error message");
    println!("Value is {}", value);

    // using the ? operator to handle errors
    test_question_mark().unwrap();
}

// using the ? operator to handle errors
// ? can only be used in functions that return result
// it will return the error if the result is an error
// otherwise it will return the value
fn test_question_mark() -> Result<(), String> {
    let result: Result<i32, &str> = Ok(200);
    let value = result?;
    println!("Value is {}", value);
    // Ok(())
    Err("Some error message".to_string())
}

// OPTION type
// and error handling
fn test_option() {
    // creating an option type
    let option: Option<i32> = Some(200);
    println!("Option is {:#?}", option);
    let option: Option<i32> = None;

    // using the option type to handle errors
    match option {
        Some(value) => println!("Option is {}", value),
        None => println!("Option is None"),
    }

    // using unwrap to handle errors
    // unwrap will return the value if the option is Some
    // otherwise it will panic
    let value = option.unwrap();
    println!("Value is {}", value);

    // using expect to handle errors
    // expect will return the value if the option is Some
    // otherwise it will panic with the error message
    let value = option.expect("Some error message");
    println!("Value is {}", value);

    // using the ? operator to handle errors
    // test_option_question_mark().unwrap();
}

// extend the Path struct so that it resembles the python Path class
// https://docs.python.org/3/library/pathlib.html

// first add a path.write_text() method

// extend the Path struct wiht impl
// https://doc.rust-lang.org/std/path/struct.Path.html
// https://doc.rust-lang.org/std/fs/struct.File.html
