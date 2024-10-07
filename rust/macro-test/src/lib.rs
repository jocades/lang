//! # My Crate
//!
//! `my_crate` is a collection of utilities to make performing certain
//! calculations more convenient.

// Generate documentation:
// $ cargo doc --open

// Run doc tests:
// $ cargo test --doc

/// Adds one to the given number.
///
/// # Examples
///
/// ```
/// let arg = 5;
/// let answer = macro_test::add_one(arg);
///
/// assert_eq!(6, answer);
/// ```
pub fn add_one(x: i32) -> i32 {
    x + 1
}

/// Creates a [`Vec`] containing the arguments.
///
/// `xvec!` allows `Vec`s to be defined with the same syntax as array expressions.
/// There are two forms of this macro:
///
/// * Create a [`Vec`] containing a given list of elements:
///```
/// # use macro_test::xvec;
/// let v = xvec![1, 2, 3];
/// assert_eq!(v[0], 1);
/// assert_eq!(v[1], 2);
/// assert_eq!(v[2], 3);
///```
#[macro_export]
macro_rules! xvec {
    ($($item:expr),*) => {{
        let mut v = Vec::new();
        $(v.push($item);)*
        v
    }};
    ($($item:expr,)*) => {{
        $crate::xvec![$($item),*]
    }};
    ($item:expr; $len:expr) => {{
        let mut v = Vec::new();
        v.resize($len, $item);
        v
    }};
}

#[allow(unused)]
/// Tests a [`xvec`].
///
///```
/// # use macro_test::xvec;
/// let v = xvec![0; 3];
/// assert_eq!(v, [0, 0, 0]);
///```
pub fn test_xvec() {
    let v1: Vec<u8> = xvec![];
    let v2 = xvec![1, 2, 3];
    let v3 = xvec![0; 3];

    let v1: Vec<u8> = vec![];
    let x1 = vec![0; 3];
    let x2 = vec![1, 2, 3];

    use std::prelude::rust_2021::*;
}
