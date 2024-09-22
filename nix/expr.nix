let
  a = { x = 1; y = 2; };
in
{
  inherit (a) x y;
}
