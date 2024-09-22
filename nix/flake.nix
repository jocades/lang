{
  description = "A very basic flake";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-23.05-darwin";
  };

  outputs = { self, nixpkgs }: {
    packages.aarch64-darwin.default = nixpkgs.legacyPackages.aarch64-darwin.buildEnv {
      name = "jordis-env";
      paths = with nixpkgs.legacyPackages.aarch64-darwin; [
        cowsay
        lolcat
      ];
      pathsToLink = [
        "/bin"
        "/lib"
        "/share/man"
        "/share/doc"
      ];
      extraOutputsToInstall = [ "man" "out" ];
    };

    devShells.aarch64-darwin.default = nixpkgs.legacyPackages.aarch64-darwin.mkShell {
      name = "devshell";
      buildInputs = with nixpkgs.legacyPackages.aarch64-darwin; [
        cowsay
        lolcat
      ];
    };
  };
}
