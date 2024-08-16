fn main() {
    let input = String::from("key");
    p1(&input);
}

fn p1(input: &str) {
    p2(input);
}

fn p2(_input: &str) {
    // finally use the string i.e:
    db.insert(input.to_string(), value);
}
