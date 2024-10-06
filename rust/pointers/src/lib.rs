#![allow(unused, private_interfaces)]

mod cell;
mod raw;
mod rc;
mod refcell;

use raw::MyReader;

fn test() {
    let reader = MyReader::default();
    let pos = reader.pos();
}
