#![allow(unused, private_interfaces)]

mod cell;
mod dyna;
mod raw;
mod rc;
mod refcell;
mod vec;
mod vec_logic_compression;

use raw::MyReader;

fn test() {
    let reader = MyReader::default();
    let pos = reader.pos();
}
