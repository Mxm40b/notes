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
        # export LIBGL_DRIVERS_PATH=${pkgs.mesa}/lib/dri
        # export LD_LIBRARY_PATH =${pkgs.lib.makeLibraryPath[
        #   pkgs.glfw
        #   pkgs.mesa
        #   pkgs.glew
        #   pkgs.wayland
        #   pkgs.wayland-protocols
        #   pkgs.libGL
        # ]}
}
