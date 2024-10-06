{
  readTOML = path: builtins.fromTOML (builtins.readFile path);
}
