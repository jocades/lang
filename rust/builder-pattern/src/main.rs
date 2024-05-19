mod builder;
mod prelude;

use builder::RequestBuilder;
use prelude::*;

fn main() -> Result<()> {
    let mut builder = RequestBuilder::new();
    builder.url("https://some-url.com").method("GET");

    // do stuff...

    let req = builder.header("x-api-token", "abc").build()?;
    println!("{req:#?}");

    // do stuff...

    builder.header("client version", "1.2");
    let req = builder.build()?;
    println!("{req:#?}");

    Ok(())
}
