use std::fs;
use std::path::Path;
use std::process;

#[derive(Debug)]
pub struct Config {
    pub source: String,
    pub output: String,
}

impl Config {
    pub fn new(args: &[String]) -> Result<Config, &'static str> {
        if args.len() < 2 {
            return Err("not enough arguments");
        }

        // map the correct arguments which could come in two forms:
        // 1. cargo run <source> -o <output>
        // 2. cargo run -o <output> <source>
        // find the -o flag and map the source and output accordingly
        // if the -o flag is not found, use the source name but change the extensiono to .out

        let mut source = String::new();
        let mut output = String::new();

        let mut output_flag = false;

        for arg in args.iter() {
            if arg == "-o" {
                output_flag = true;
                continue;
            }

            if output_flag {
                output = arg.clone();
                output_flag = false;
            } else {
                source = arg.clone();
            }
        }

        if output.is_empty() {
            output = Path::new(&source)
                .with_extension("out")
                .to_str()
                .unwrap()
                .to_string();
        }

        Ok(Config { source, output })
    }
}

// stack based language

/* 10 20 + puts
push 20 to stack
push 10 to stack
add the top two elements and push the result to the stack
print the top element of the stack and remove it from the stack
-> 30 */

/*
proc add
    pop a
    pop b
    push a + b
end
*/

pub fn run(config: Config) -> Result<(), Box<dyn std::error::Error>> {
    let source = fs::read_to_string(config.source)?;

    let mut stack = Vec::new();

    for line in source.lines() {
        let mut tokens = line.split_whitespace();

        while let Some(token) = tokens.next() {
            match token {
                "proc" => {
                    let proc_name = tokens.next().unwrap();
                    let mut proc_tokens = Vec::new();

                    while let Some(token) = tokens.next() {
                        if token == "end" {
                            break;
                        }

                        proc_tokens.push(token);
                    }

                    // println!("{:?}", proc_tokens);
                }
                "+" => {
                    let a = stack.pop().unwrap();
                    let b = stack.pop().unwrap();
                    stack.push(a + b);
                }
                "-" => {
                    let a = stack.pop().unwrap();
                    let b = stack.pop().unwrap();
                    stack.push(b - a);
                }
                "*" => {
                    let a = stack.pop().unwrap();
                    let b = stack.pop().unwrap();
                    stack.push(a * b);
                }
                "/" => {
                    let a = stack.pop().unwrap();
                    let b = stack.pop().unwrap();
                    stack.push(b / a);
                }
                "%" => {
                    let a = stack.pop().unwrap();
                    let b = stack.pop().unwrap();
                    stack.push(b % a);
                }
                "puts" => {
                    println!("{}", stack.pop().unwrap());
                }

                _ => {
                    stack.push(token.parse::<i32>().unwrap());
                }
            }
        }
    }

    Ok(())
}
