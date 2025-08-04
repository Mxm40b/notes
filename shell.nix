{
  pkgs ? import <nixpkgs> { },
}:

pkgs.mkShell {
  name = "devenv";

  buildInputs = with pkgs; [
    cmake
    clang-tools
    cmake-language-server
    gcc
  ];
  shellHook = ''
    exec nu
  '';
}
