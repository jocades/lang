use std::fs;
use std::path::Path;

// extend the Path struct so that it resembles the python Path class
// https://docs.python.org/3/library/pathlib.html

// first add a path.write_text() method

// extend the Path struct wiht impl
// https://doc.rust-lang.org/std/path/struct.Path.html
// https://doc.rust-lang.org/std/fs/struct.File.html

impl Path {
    // write_text method
    pub fn write_text(&self, text: &str) -> std::io::Result<()> {
        // Open a file in write-only mode, returns `io::Result<File>`
        let mut file = match fs::File::create(&self) {
            Err(why) => panic!("couldn't create {}: {}", self.display(), why),
            Ok(file) => file,
        };

        // Write the `text` string to `file`, returns `io::Result<()>`
        file.write_all(text.as_bytes())
    }
}
