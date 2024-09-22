#![allow(unused)]
use crate::prelude::*;

#[derive(Debug)]
pub struct Request {
    pub url: String,
    pub method: String,                 // should be enum
    pub headers: Vec<(String, String)>, // (key, value)
    pub body: Option<String>,
}

#[derive(Default)]
pub struct RequestBuilder {
    pub url: Option<String>,
    pub method: Option<String>,
    pub headers: Vec<(String, String)>,
    pub body: Option<String>,
}

impl RequestBuilder {
    pub fn new() -> Self {
        RequestBuilder::default()
    }

    pub fn url(&mut self, url: impl Into<String>) -> &mut Self {
        self.url = Some(url.into());
        self
    }

    pub fn method(&mut self, method: impl Into<String>) -> &mut Self {
        self.method = Some(method.into());
        self
    }

    pub fn body(&mut self, body: impl Into<String>) -> &mut Self {
        self.body = Some(body.into());
        self
    }

    pub fn header(
        &mut self,
        key: impl Into<String>,
        value: impl Into<String>,
    ) -> &mut Self {
        self.headers.push((key.into(), value.into()));
        self
    }

    pub fn build(&self) -> Result<Request> {
        let Some(url) = self.url.as_ref() else {
            return Err(Error::Static("No URL"));
        };
        let method = self
            .method
            .as_ref()
            .cloned()
            .unwrap_or_else(|| "GET".into());

        Ok(Request {
            url: url.to_string(),
            method,
            headers: self.headers.clone(),
            body: self.body.clone(),
        })
    }
}
