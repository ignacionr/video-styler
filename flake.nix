{
  description = "Video Styler - Neural Style Transfer for Videos";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
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
            # Build tools
            cmake
            ninja
            pkg-config
            
            # Compilers
            gcc13
            clang_17
            
            # Libraries
            opencv4
            eigen
            boost
            
            # Testing
            gtest
            
            # Development tools
            gdb
            clang-tools
            
            # Documentation
            doxygen
            
            # Additional utilities
            git
            curl
            wget
          ];

          shellHook = ''
            echo "Video Styler Development Environment"
            echo "=================================="
            echo "OpenCV version: $(pkg-config --modversion opencv4)"
            echo "GCC version: $(gcc --version | head -n1)"
            echo "CMake version: $(cmake --version | head -n1)"
            echo ""
            echo "Available commands:"
            echo "  mkdir build && cd build && cmake .. && make"
            echo "  ctest  # Run tests"
            echo ""
          '';

          # Set environment variables
          CMAKE_BUILD_TYPE = "Debug";
          OPENCV_DIR = "${pkgs.opencv4}";
        };
      });
}
