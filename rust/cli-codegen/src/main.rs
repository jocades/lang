use clap::Parser;
// use Path and file io
use std::fs;
use std::path::Path;
use std::process;

#[derive(Parser, Debug)]
#[command(version, about, long_about = None)]
struct Cli {
    name: String,

    #[arg(short = 's', long)]
    with_state: bool,

    #[arg(short = 'e', long)]
    with_effect: bool,
}

fn main() {
    let args = Cli::parse();

    println!("{:?}", args);

    let path = Path::new(&args.name);
    println!("path: {:?}", path);

    let parent = path.parent().unwrap_or_else(|| {
        eprintln!("invalid path");
        process::exit(1);
    });

    println!("parent: {:?}", parent);

    // create the dirs if they don't exist
    fs::create_dir_all(parent).unwrap_or_else(|_| {
        eprintln!("unable to create dir");
        process::exit(1);
    });

    let name = path.file_stem().unwrap().to_str().unwrap();
    let name = kebab_to_pascal_case(name);
    println!("name: {}", name);

    let path = path.with_extension("tsx");
    let templ = Template::new(args);
    let content = templ.render();

    fs::write(path, content).unwrap_or_else(|_| {
        eprintln!("unable to create file");
        process::exit(1);
    });
}

fn capitalize(s: &str) -> String {
    let mut chars = s.chars();
    match chars.next() {
        None => String::new(),
        Some(c) => c.to_uppercase().chain(chars).collect(),
    }
}

fn kebab_to_pascal_case(s: &str) -> String {
    s.split('-').map(capitalize).collect()
}

/* const template = {
  useState: `const [state, setState] = useState()`,
  useEffect: `useEffect(() => {}, [])`,
  imports(opts: Options) {
    return (
      (opts.withState || opts.withEffect) &&
      `import { ${opts.withState ? 'useState' : ''}${
        opts.withState && opts.withEffect ? ', ' : ''
      }${opts.withEffect ? 'useEffect' : ''} } from 'react'`
    )
  },
} */

struct Template {
    args: Cli,
}

impl Template {
    fn new(args: Cli) -> Self {
        Self { args }
    }

    fn use_state(&self) -> &'static str {
        "const [state, setState] = useState()"
    }

    fn use_effect(&self) -> &'static str {
        "useEffect(() => {}, [])"
    }

    fn import(&self) -> String {
        let mut imports = String::new();

        if self.args.with_state || self.args.with_effect {
            imports.push_str("import { ");
            if self.args.with_state {
                imports.push_str("useState");
            }
            if self.args.with_state && self.args.with_effect {
                imports.push_str(", ");
            }
            if self.args.with_effect {
                imports.push_str("useEffect");
            }
            imports.push_str(" } from 'react'");
        }

        imports
    }

    fn render(&self) -> String {
        format!(
            r#"{import}
    export default function {name}() {{
        {state}
        return <div>{name}</div>;
    }}"#,
            import = self.import(),
            state = if self.args.with_state {
                self.use_state().to_owned() + "\n"
            } else {
                "".to_owned()
            },
            name = kebab_to_pascal_case(&self.args.name)
        )
    }
}
