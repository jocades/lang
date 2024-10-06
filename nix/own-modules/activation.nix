{
  config,
  lib,
  pkgs,
  ...
}:

let
  cfg = config.myActivation;
in
{
  options.myActivation = {
    enable = lib.mkEnableOption "custom activation script";
    script = lib.mkOption {
      type = lib.types.lines;
      default = "";
      description = "Shell command to run during acitvation";
    };
  };

  config = lib.mkIf cfg.enable {
    system.build.activate = pkgs.writeShellScriptBin "acitvate" ''
      echo "Running custom activation script..."

      if [ -d ~/.config/wezterm ]; then
        echo "Wezterm exists!"
      fi

      ${cfg.script}

      echo "Activation complete!"
    '';
  };
}
