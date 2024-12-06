mod encode;
use encode::Encode;

mod decode;
use decode::Decode;

use clap::Subcommand;

#[derive(Subcommand)]
pub enum Command {
    Encode(Encode),
    Decode(Decode),
}

impl Command {
    pub fn execute(&self) -> crate::Result<()> {
        use Command::*;
        match self {
            Encode(cmd) => cmd.execute(),
            Decode(cmd) => cmd.execute(),
        }
    }
}
