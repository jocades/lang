use std::io::{self, BufRead, BufReader, Read};

#[derive(Default)]
pub struct MyReader<'a> {
    content: &'a [u8],
    pos: usize,
}

impl MyReader<'_> {
    pub fn new<'a>(content: &'a [u8]) -> MyReader<'a> {
        MyReader { content, pos: 0 }
    }

    pub fn pos(&self) -> usize {
        self.pos
    }
}

impl Read for MyReader<'_> {
    fn read(&mut self, buf: &mut [u8]) -> std::io::Result<usize> {
        if self.pos >= self.content.len() {
            return Ok(0); // We've reached the end of the content (EOF)
        }

        let n = std::cmp::min(buf.len(), self.content.len() - self.pos);
        buf[..n].copy_from_slice(&self.content[self.pos..self.pos + n]);
        self.pos += n;

        Ok(n)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn first_word(s: &str) -> &str {
        &s[..]
    }

    fn what<T: AsRef<str>>(v: T) {
        first_word(v.as_ref());
    }

    #[test]
    fn my_reader() {
        let mut v = String::from("hello");
        let first = first_word(&v);
        v.clear();
        println!("{first}");

        let mut reader = MyReader::new([1, 2, 3, 4, 5].as_ref());

        let mut buf = [0; 3];
        assert_eq!(reader.read(&mut buf).unwrap(), 3);
        assert_eq!(buf, [1, 2, 3]);

        let mut buf = [0; 3];
        assert_eq!(reader.read(&mut buf).unwrap(), 2);
        assert_eq!(buf, [4, 5, 0]);

        let mut buf = [0; 3];
        assert_eq!(reader.read(&mut buf).unwrap(), 0);
        assert_eq!(buf, [0, 0, 0]);

        let mut reader = BufReader::new(reader);
    }
}
