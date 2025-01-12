use std::{
    fs,
    io::{prelude::*, BufReader},
    net::{TcpListener, TcpStream},
    thread,
    time::Duration,
};

fn main() {
    let listener = TcpListener::bind("127.0.0.1:6969").unwrap();

    for stream in listener.incoming() {
        let stream = stream.unwrap();

        handle_connection(stream);
    }
}

#[derive(Debug)]
struct Request {
    method: String,
    path: String,
    version: String,
}

impl Request {
    fn new(buf_reader: BufReader<&mut TcpStream>) -> Self {
        let req_line = buf_reader.lines().next().unwrap().unwrap();

        let mut parts = req_line.split_whitespace();
        let method = parts.next().unwrap();
        let path = parts.next().unwrap();
        let version = parts.next().unwrap();

        // TODO: parse headers now and method to parse body later

        Request {
            method: method.to_string(),
            path: path.to_string(),
            version: version.to_string(),
        }
    }
}

fn handle_connection(mut stream: TcpStream) {
    let buf_reader = BufReader::new(&mut stream);

    let request = Request::new(buf_reader);
    println!("{:#?}", request);

    let (status, filename) = match &request.path[..] {
        "/" => ("HTTP/1.1 200 OK", "hello.html"),
        "/sleep" => {
            thread::sleep(Duration::from_secs(5));
            ("HTTP/1.1 200 OK", "hello.html")
        }
        _ => ("HTTP/1.1 404 NOT FOUND", "404.html"),
    };

    let contents = fs::read_to_string(filename).unwrap();
    let length = contents.len();

    let response =
        format!("{status}\r\nContent-Length: {length}\r\n\r\n{contents}");

    stream.write_all(response.as_bytes()).unwrap();
}
