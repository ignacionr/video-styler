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
            cmake # Latest stable 4.0.x series
            ninja
            pkg-config
            
            # Compilers - Use latest available in nixpkgs
            # Note: Clang 20 might not be available yet in nixpkgs, using latest available
            clang_18  # Will try to use the latest available
            llvm_18   # LLVM tools
            
            # Libraries
            opencv4   # Latest OpenCV 4.x series (target: 4.12.0)
            eigen     # Latest Eigen3
            boost182  # Latest Boost 1.82+
            
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
            echo "Updated with latest tool versions (Aug 2025):"
            echo "  CMake version: $(cmake --version | head -n1)"
            echo "  Clang version: $(clang --version | head -n1)"
            echo "  OpenCV version: $(pkg-config --modversion opencv4 2>/dev/null || echo 'N/A')"
            echo "  Boost version: $(echo '#include <boost/version.hpp>' | clang++ -x c++ -E -dM - | grep 'BOOST_LIB_VERSION' | cut -d'"' -f2 2>/dev/null || echo 'N/A')"
            echo ""
            echo "C++23 Standard Features Available"
            echo ""
            echo "Build commands:"
            echo "  mkdir -p build && cd build"
            echo "  cmake -GNinja .."
            echo "  ninja"
            echo "  ctest --verbose  # Run tests"
            echo ""
          '';

          # Set environment variables for modern C++ development
          CMAKE_BUILD_TYPE = "Debug";
          CMAKE_GENERATOR = "Ninja";
          OPENCV_DIR = "${pkgs.opencv4}";
          CXX_STANDARD = "23";
          # Enable latest language features
          CXXFLAGS = "-std=c++23 -Wall -Wextra -Wpedantic";
        };
      });
}
