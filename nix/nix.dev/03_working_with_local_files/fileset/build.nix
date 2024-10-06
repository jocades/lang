{ stdenv, lib }:
let
  fs = lib.fileset;
  sourceFiles = ./.;
in

fs.trace sourceFiles

stdenv.mkDerivation {
  name = "fileset";
  src = fs.toSource {
    root = ./.;
    fileset = fs.difference ./. (fs.maybeMissing ./result);
  };
  postInstall = ''
    mkdir $out
    cp -v {hello,world}.txt $out
  '';
}
