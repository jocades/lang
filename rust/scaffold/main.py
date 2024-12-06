import os
import subprocess


def snake_to_pascal_case(what: str):
    return "".join(map(str.capitalize, what.split("_")))


def create_project(name: str):
    subprocess.run(["cargo", "new", name], check=True)
    os.chdir(name)


def add_dependency():
    try:
        # Try using cargo add first
        subprocess.run(["cargo", "add", "clap", "--features", "derive"], check=True)
    except subprocess.CalledProcessError:
        print("Unable to add clap dependency")
        exit(1)


def create_directory_structure():
    os.makedirs("src/cmd", exist_ok=True)


def update_readme(name):
    readme_content = f"""# {name}
A CLI application for [...].

## Commands

[List and describe your commands here]

## Usage

[Provide usage instructions here]"""
    with open("README.md", "w") as f:
        f.write(readme_content)


def create_main_rs():
    main_rs = f"""mod cmd;
use clap::Parser;

type Result<T> = std::result::Result<T, Box<dyn std::error::Error>>;

#[derive(Parser)]
#[command(author, version, about, long_about = None)]
struct Cli {{
    #[command(subcommand)]
    command: cmd::Command,
}}

fn main() -> Result<()> {{
    let cli = Cli::parse();
    cli.command.execute()
}}"""
    with open("src/main.rs", "w") as f:
        f.write(main_rs)


def create_cmd_mod_rs(commands):
    imports = "\n".join(
        f"mod {cmd};\nuse {cmd}::{cmd.capitalize()};" for cmd in commands
    )
    enum_variants = "\n    ".join(
        f"{cmd.capitalize()}({cmd.capitalize()})," for cmd in commands
    )
    match_arms = "\n            ".join(
        f"{cmd.capitalize()}(cmd) => cmd.execute()," for cmd in commands
    )

    cmd_mod_rs = f"""{imports}

use clap::Subcommand;

#[derive(Subcommand, Debug)]
pub enum Command {{
    {enum_variants}
}}

impl Command {{
    pub fn execute(&self) -> crate::Result<()> {{
        use Command::*;
        match self {{
            {match_arms}
        }}
    }}
}}"""
    with open("src/cmd/mod.rs", "w") as f:
        f.write(cmd_mod_rs)


def create_command_file(command):
    command_file = f""" use clap::Args;

#[derive(Args, Debug)]
pub struct {command.capitalize()} {{
    // Add command-specific arguments here
}}

impl {command.capitalize()} {{
    pub fn execute(&self) -> crate::Result<()> {{
        // Implement command logic here
        println!("{command.capitalize()} command executed");
        Ok(())
    }}
}}"""
    with open(f"src/cmd/{command}.rs", "w") as f:
        f.write(command_file)


def main():
    project_name = input("Enter the project name: ")
    commands = input("Enter command names (space-separated): ").split()

    create_project(project_name)
    add_dependency()
    create_directory_structure()
    update_readme(project_name)
    create_main_rs()
    create_cmd_mod_rs(commands)

    for command in commands:
        create_command_file(command)

    print(f"Scaffold for {project_name} created successfully!")


if __name__ == "__main__":
    main()
