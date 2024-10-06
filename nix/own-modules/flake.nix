{
  description = "Darwin System";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    external = {
      url = "path:/Users/j0rdi/prog/lang/nix/own-modules/external-flake";
      inputs.nixpkgs.follows = "nixpkgs";
    };

  };

  outputs =
    {
      self,
      nixpkgs,
      external,
    }:
    let
      host = "Jordis-MacBook-Pro";
      system = "aarch64-darwin";
      pkgs = nixpkgs.legacyPackages.${system};

      configuration =
        {
          config,
          lib,
          pkgs,
          ...
        }:
        {
          # ...
        };
    in
    {
      mySystem = pkgs.lib.evalModules {
        modules = [
          ./system.nix
          ./activation.nix
          {
            _module.args = {
              inherit pkgs;
            };
            myActivation = {
              enable = true;
              script = ''
                echo "Hello from my custom actiovation script!"
                echo "Current date: $(date)"
              '';
            };
          }
        ];
      };

      inherit external;
    };
}
