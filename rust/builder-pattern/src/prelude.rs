//! Crate prelude
#![allow(unused)]

#[derive(Debug)]
pub enum Error {
    /// For starter, to remove as code matures
    Generic(String),
    /// For starter, to remove as code matures
    Static(&'static str),
}

pub type Result<T> = core::result::Result<T, Error>;

// Wrapper tuple struct for newtype pattern,
// mostly for external type to type From/TryFrom conversions
pub struct W<T>(pub T);
