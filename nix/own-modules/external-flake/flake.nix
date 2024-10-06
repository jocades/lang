{
  description = "A very basic flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
  };

  outputs =
    { self, nixpkgs }:
    let
      system = builtins.currentSystem;
      rev = self.rev or self.dirtyRev or null;
      pkgs = nixpkgs.legacyPackages.${system};
      lib = pkgs.lib;

      homeDir = "/Users/j0rdi";
      configDir = homeDir + "/.config";
      dotsDir = homeDir + "";
      path = ./wez.lua;
      configPath = "/Users/j0rdi/.config";
      mkSymLink = path: configPath + (lib.removePrefix (toString self) (toString path));
      link = mkSymLink path;

    in
    {
      inherit self;
      inherit pkgs;
      inherit lib;

      inherit system;
      inherit link;
      inherit mkSymLink;
      inherit path;
      inherit configPath;
    };
}
