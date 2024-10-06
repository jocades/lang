trait Hei {
    fn hei(&self, v: &str);
}

struct Other;

impl Hei for Other {
    fn hei(&self, v: &str) {
        println!("Hey! {}", v)
    }
}

fn take_hei_gen<T: Hei>(v: &T) {
    v.hei("gen");
}

fn take_hei_impl(v: &impl Hei) {
    v.hei("impl");
}

fn take_hei_dyn(v: &dyn Hei) {
    v.hei("dyn");
}

fn take_slice_hei_impl(v: &[impl Hei]) {
    v[1].hei("slice impl");
}

fn main() {
    let o = Other;
    take_hei_gen(&o);
    take_hei_impl(&o);
    take_hei_dyn(&o);

    let os = vec![Other, Other];
    take_slice_hei_impl(&os);

    let args = ["--one", "--two"];
}
