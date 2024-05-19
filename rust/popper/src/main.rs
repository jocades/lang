use std::env;
use std::fs;
use std::path::Path;
use std::process;

use popper::Config;

fn main() {
    let args: Vec<String> = env::args().collect();

    let config = Config::new(&args).unwrap_or_else(|err| {
        eprintln!("Problem parsing arguments: {}", err);
        process::exit(1);
    });

    println!("{:?}", config);

    if let Err(e) = popper::run(config) {
        eprintln!("Application error: {}", e);
        process::exit(1);
    }
}
