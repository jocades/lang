use std::time::Duration;

fn main() {
    let seq: Vec<usize> = (0..9).collect();
    let mut i = 0;
    loop {
        let n = seq[i];
        println!("index = {i} value = {n}");
        i = (i + 1) % seq.len();
        std::thread::sleep(Duration::from_millis(200));
    }
}
