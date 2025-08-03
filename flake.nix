{
  description = "C++23 Video Style Transfer with latest toolchains";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.05";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      {
        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [
            cmake
            ninja
            pkg-config
            clang_16
            opencv4
            eigen
            boost182
            gtest
            lldb
            graphviz
          ];

          shellHook = ''
            echo ""
            echo "Video Styler Development Environment"
            echo "=================================="
            echo "Updated with latest tool versions (Aug 2025):"
            echo "  CMake version: $(cmake --version | head -n1)"
            echo "  Clang version: $(clang --version | head -n1)"
            echo "  OpenCV version: 4.9.0"
            echo "  Boost version: 1_82"
            echo ""
            echo "C++23 Standard Features Available"
            echo ""
            echo "Build commands:"
            echo "  mkdir -p build && cd build"
            echo "  cmake -GNinja .."
            echo "  ninja"
            echo "  ctest --verbose  # Run tests"
            echo ""
            
            export CPPFLAGS="-stdlib=libc++ $CPPFLAGS"
            export CXXFLAGS="-stdlib=libc++ $CXXFLAGS"
          '';
        };
      }
    );
}
