{
  description = "A very basic flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs }: 
  let
    pkgs = nixpkgs.legacyPackages.aarch64-darwin;
  in
  {
    packages.aarch64-darwin.hello = pkgs.hello;

    packages.aarch64-darwin.default = self.packages.aarch64-darwin.hello;
    devShells.aarch64-darwin.default = pkgs.mkShell {
        buildInputs = [];
      };

  };
}
