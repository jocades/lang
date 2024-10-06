{
  description = "Testing flakes";
  inputs = { };
  outputs =
    { ... }:
    let
      who = "jordi";
    in
    {
      inherit who;
    };
}
