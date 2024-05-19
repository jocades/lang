use std::collections::HashMap;

fn main() {
    println!("Hello, world!");
    // sort_by_length()
}

fn square_digits(num: u64) -> u64 {
    // static str type. created ad compile time and located in the binary so we can accesss it form
    // any where at any time at runtime
    let s: &'static str = "hello";
    // same as
    let s = "hello"; // -> &str | &'static str

    // 9119 -> 'n1^2' 'n2^2 ...' -> 81 1 1 81
    /* let mut result = String::new();

    for c in num.to_string().chars() {
        let digit = c.to_digit(10).unwrap();
        result.push_str(&(digit * digit).to_string());
    }

    result.parse::<u64>().unwrap() */

    // or
    num.to_string()
        .chars()
        .fold(String::new(), |acc, c| {
            acc + &c.to_digit(10).unwrap().pow(2).to_string()
        })
        .parse::<u64>()
        .unwrap()
}

/* #[cfg(test)]
mod tests {
    use super::square_digits;

    #[test]
    fn test_square_digits() {
        assert_eq!(square_digits(9119), 811181, "\nFailed with num 9119");
    }
}

fn number(bus_stops: &[(i32, i32)]) -> i32 {
    bus_stops.iter().fold(0, |acc, (on, off)| acc + (on - off))
} */

/* #[test]
fn returns_expected() {
    assert_eq!(number(&[(10, 0), (3, 5), (5, 8)]), 5);
    assert_eq!(
        number(&[(3, 0), (9, 1), (4, 10), (12, 2), (6, 1), (7, 10)]),
        17
    );
    assert_eq!(
        number(&[(3, 0), (9, 1), (4, 8), (12, 2), (6, 1), (7, 8)]),
        21
    );
} */

fn sort_by_length(arr: &[String]) -> Vec<String> {
    // let mut res = arr.to_vec();
    // res.sort_by_key(|x, y| x.len().cmp(&y.len()));
    // res
    // or

    let mut arr = arr.to_vec();
    arr.sort_by_key(String::len);
    arr
}

#[cfg(test)]
mod tests {
    use super::sort_by_length;

    fn dotest(arr: &[String], expected: &[String]) {
        let actual = sort_by_length(arr);
        assert!(
            actual == expected,
            "With arr = {arr:?}\nExpected {expected:?} but got {actual:?}"
        )
    }

    #[test]
    fn fixed_tests() {
        dotest(
            &[
                String::from("beg"),
                String::from("life"),
                String::from("i"),
                String::from("to"),
            ],
            &[
                String::from("i"),
                String::from("to"),
                String::from("beg"),
                String::from("life"),
            ],
        );
        dotest(
            &[
                String::from(""),
                String::from("moderately"),
                String::from("brains"),
                String::from("pizza"),
            ],
            &[
                String::from(""),
                String::from("pizza"),
                String::from("brains"),
                String::from("moderately"),
            ],
        );
        dotest(
            &[
                String::from("longer"),
                String::from("longest"),
                String::from("short"),
            ],
            &[
                String::from("short"),
                String::from("longer"),
                String::from("longest"),
            ],
        );
        dotest(
            &[
                String::from("dog"),
                String::from("food"),
                String::from("a"),
                String::from("of"),
            ],
            &[
                String::from("a"),
                String::from("of"),
                String::from("dog"),
                String::from("food"),
            ],
        );
        dotest(
            &[
                String::from(""),
                String::from("dictionary"),
                String::from("eloquent"),
                String::from("bees"),
            ],
            &[
                String::from(""),
                String::from("bees"),
                String::from("eloquent"),
                String::from("dictionary"),
            ],
        );
        dotest(
            &[
                String::from("a longer sentence"),
                String::from("the longest sentence"),
                String::from("a short sentence"),
            ],
            &[
                String::from("a short sentence"),
                String::from("a longer sentence"),
                String::from("the longest sentence"),
            ],
        );
    }
}

fn comp(a: Vec<i64>, b: Vec<i64>) -> bool {
    if a.len() != b.len() {
        return false;
    }

    let mut a = a.iter().map(|x| x.pow(2)).collect::<Vec<i64>>();
    a.sort();
    let mut b = b.to_vec();
    b.sort();

    a == b
}

fn testing(a: Vec<i64>, b: Vec<i64>, exp: bool) -> () {
    assert_eq!(comp(a, b), exp)
}

#[test]
fn tests_comp() {
    let a1 = vec![121, 144, 19, 161, 19, 144, 19, 11];
    let a2 = vec![
        11 * 11,
        121 * 121,
        144 * 144,
        19 * 19,
        161 * 161,
        19 * 19,
        144 * 144,
        19 * 19,
    ];
    testing(a1, a2, true);

    let a1 = vec![121, 144, 19, 161, 19, 144, 19, 11];
    let a2 = vec![
        11 * 21,
        121 * 121,
        144 * 144,
        19 * 19,
        161 * 161,
        19 * 19,
        144 * 144,
        19 * 19,
    ];
    testing(a1, a2, false);
}
