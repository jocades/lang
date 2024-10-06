{
  config,
  lib,
  pkgs,
  ...
}:

{
  options = {
    system.build = lib.mkOption {
      type = lib.types.attrsOf lib.types.anything;
      default = { };
      description = "Attribute set of derivations used to setup the system.";
    };
  };
}
