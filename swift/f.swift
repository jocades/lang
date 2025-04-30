func what(_ name: String, cb: () -> Void) {
  print("Executing \(name)...")
  cb()
}

what("callback", cb: { print("work") }) 

