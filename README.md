# Video Styler

A C++23 application that applies Neural Style Transfer to videos frame-by-frame using OpenCV.

## Features

- Neural Style Transfer processing
- Frame-by-frame video transformation
- Modern C++23 codebase
- Comprehensive testing with Google Test

## Requirements

- Nix package manager
- CMake 3.25+
- C++23 compatible compiler (GCC 13+ or Clang 17+)
- OpenCV 4.x
- Eigen3
- Boost
- Google Test

## Building

### Using Nix (Recommended)

1. Enter the development environment:
   ```bash
   nix develop
   ```

2. Build the project:
   ```bash
   mkdir build && cd build
   cmake ..
   make -j$(nproc)
   ```

### Manual Build

If you have all dependencies installed manually:

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)
```

## Running

```bash
./build/src/video_styler --input input_video.mp4 --output styled_video.mp4 --style style_image.jpg
```

## Testing

Run the test suite:

```bash
cd build
ctest --verbose
```

Or run specific tests:

```bash
./tests/video_styler_tests
```

## Project Structure

```
video-styler/
├── src/                    # Source files
│   ├── main.cpp           # Main application entry point
│   ├── video_processor/   # Video processing modules
│   ├── style_transfer/    # Neural style transfer implementation
│   └── utils/             # Utility functions
├── include/               # Header files
│   ├── video_processor/   # Video processing headers
│   ├── style_transfer/    # Style transfer headers
│   └── utils/             # Utility headers
├── tests/                 # Unit tests
├── docs/                  # Documentation
├── examples/              # Example videos and styles
├── build/                 # Build directory (generated)
├── flake.nix             # Nix development environment
├── CMakeLists.txt        # CMake configuration
└── README.md             # This file
```

## Development

This project uses:
- **C++23** for modern language features
- **Nix** for reproducible development environment
- **CMake** for build system
- **Google Test** for unit testing
- **OpenCV** for video and image processing
- **Eigen** for linear algebra operations

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests for new functionality
5. Ensure all tests pass
6. Submit a pull request

## License

[Add your license here]
