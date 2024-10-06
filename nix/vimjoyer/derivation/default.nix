{
  pkgs ? import <nixpkgs> { },
}:

pkgs.stdenv.mkDerivation {
  name = "hello-world";
  src = ./src;

  buildPhase = ''
    g++ hello.cpp -o hello
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp $src/hello $out/bin
  '';
}
