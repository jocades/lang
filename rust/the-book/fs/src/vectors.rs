enum Cell {
    Empty,
    Value(i32),
}

pub fn test() {
    let v = vec![1, 2, 3];

    // let third = &v[3];
    // println!("The third element is {}", third); // error: index out of bounds
    let third: Option<&i32> = v.get(2);
    match third {
        Some(value) => println!("The third element is {}", value),
        None => println!("There is no third element"),
    }
    // or
    let third = match v.get(2) {
        Some(value) => value,
        None => &0,
    };
    println!("The third element is {}", third);
    // or
    if let Some(value) = v.get(3) {
        println!("The third element is {}", value);
    } else {
        println!("There is no third element");
    }

    // Vector of tuples
    let mut x: Vec<(String, i32)> = Vec::new();

    // Pushing to a vector
    x.push(("one".to_string(), 1));

    /* let mut new_vec = pass_me_a_vec(vec![
        ("one".to_string(), 1),
        ("two".to_string(), 2),
        ("three".to_string(), 3),
    ]); */
    let mut new_vec = pass_me_a_vec(&mut x);

    x.push(("two".to_string(), 2));

    new_vec.push("four".to_string());
    new_vec.iter().for_each(|s| println!("new vec: {}", s));

    // string methods what are the main diffs btw &str and String
    let s: &str = "hello";

    // all theese methods convert &str to String
    let y = s.to_string();
    let y = "hello".to_uppercase();

    // this one is a bit different because it takes a reference to a string
    let y = " hello ".trim();

    // how to convert a String to &str
    let s: String = "hello".to_string();
    let y: &str = &s;

    let u: &str = &"hello".to_string();

    // the usize type is an unsigned integer type with the same number of bits
    // as the platform's pointer type. So on a 32-bit system, usize is a 32-bit
    // unsigned integer, and on a 64-bit system, usize is a 64-bit unsigned integer.
    //
    // this means that the usize type is used to store the size of memory addresses and
    // is used to index into collections like vectors and strings.

    // this type is commonly used to index into collections because it is guaranteed to be the same size as the pointer type.
    // this means that it is guaranteed to be the same size as the memory addresses used to access the elements of the collection.
    // so it is guaranteed to be able to index into the collection without causing an overflow.

    let n: usize = 10;
    println!("n is {}", n);
    // print its size in bytes
    println!(
        "n is {} bytes, {} bits",
        std::mem::size_of_val(&n),
        std::mem::size_of_val(&n) * 8
    );
    let n: &usize = &10;
    println!("n is {}", n);
    // print its size in bytes
    println!(
        "n is {} bytes, {} bits",
        std::mem::size_of_val(&n),
        std::mem::size_of_val(&n) * 8
    );

    // loop over the values of a usize &usize
    for i in 0..*n {
        println!("i is {}", i);
    }

    // conver to i32
    // let n: i32 = n as i32;
    // println!("n is {}", n);
    // // or
    // let n: i32 = n.try_into().unwrap();
    //
    // println!("n is {}", n);

    let a = [10, 20, 30, 40]; // a plain array
                              // copy into vec
    let mut v = a.to_vec();
    // how to mutate a vec
    // v.iter_mut().for_each(|x| *x += 1);

    layered_option();
}

fn pass_me_a_vec(v: &mut Vec<(String, i32)>) -> Vec<String> {
    v.push(("four".to_string(), 4));
    // do something with the vector
    // for (s, i) in v {
    //     println!("{}: {}", s.to_uppercase(), i);
    // }
    // or
    // use for each
    v.iter()
        .for_each(|(s, i)| println!("{}: {}", s.to_uppercase(), i));
    // or map to create a new vector
    let iter = v.iter().map(|(s, _)| s.to_uppercase());

    // return a new vector
    // vec!["one".to_string(), "two".to_string()]

    iter.collect()
}

fn layered_option() {
    let range = 10;
    let mut optional_integers: Vec<Option<i8>> = vec![None];

    for i in 1..(range + 1) {
        optional_integers.push(Some(i));
    }

    let mut cursor = range;

    // TODO: make this a while let statement - remember that vector.pop also
    // adds another layer of Option<T>. You can stack `Option<T>`s into
    // while let and if let.
    // while let Some(integer) = optional_integers.pop() {
    //     assert_eq!(integer, Some(cursor));
    //     cursor -= 1;
    // }
    // make the above code work getting eerror: expected `Option<_>`, found `i8`

    while let Some(Some(integer)) = optional_integers.pop() {
        assert_eq!(integer, cursor);
        cursor -= 1;
    }

    assert_eq!(cursor, 0);
}
