#![allow(unused)]
use tracing::{event, info, info_span, span, trace, trace_span, warn, Level};

#[tokio::main]
async fn main() {
    tracing_subscriber::fmt::init();

    let span = trace_span!("main");

    // Enter the span, returning a guard object.
    let _guard = span.enter();

    let args = std::env::args();
    trace!(args = ?args, "running");

    // Any trace events that occur before the guard is dropped will occur within the span.
    do_stuff(10);

    let mut handles = Vec::new();
    for file in args {
        let handle = tokio::spawn(async move { on_thread(file).await });
        handles.push(handle);
    }

    for handle in handles {
        handle.await.unwrap();
    }
}

/// Create an instrument which will create a span for this function.
#[tracing::instrument]
async fn on_thread(file: String) {
    // let span = info_span!("file", fname = %file);
    // let _guard = span.enter();
    info!("opening the file");
    info!("reading file contents");
    info!(bytes = 34, "parsing");
    // ..
    info!(ok = true, "done with file");
}

#[tracing::instrument]
fn do_stuff(one: u8) {
    // This event will be recorded inside a span named `my_function` with the
    // field `my_arg`.
    // event!(Level::INFO, "inside my_function!");
    warn!("iniside do_stuff")
    // ...
}
