# Video Styler Documentation

## Overview

Video Styler is a C++23 application that applies Neural Style Transfer to videos frame-by-frame using OpenCV and modern C++ features.

## Architecture

### Core Components

1. **Video Processor** (`src/video_processor/`)
   - `VideoLoader`: Handles video file loading and metadata extraction
   - Provides frame-by-frame access to video content

2. **Style Transfer** (`src/style_transfer/`)
   - `NeuralStyleTransfer`: Implements neural style transfer algorithms
   - Applies artistic styles to individual frames

3. **Utilities** (`src/utils/`)
   - `Logger`: Provides logging functionality with multiple levels
   - Utility functions for common operations

### Class Hierarchy

```
VideoStyler Application
├── VideoLoader
│   ├── loadVideo()
│   ├── getFrameCount()
│   ├── getFPS()
│   └── getCapture()
├── NeuralStyleTransfer
│   ├── loadStyleImage()
│   ├── applyStyleTransfer()
│   └── setParameters()
└── Logger
    ├── info()
    ├── warning()
    ├── error()
    └── debug()
```

## Build System

### CMake Structure

- Root `CMakeLists.txt`: Main project configuration
- `src/CMakeLists.txt`: Source files and linking
- `tests/CMakeLists.txt`: Test configuration with Google Test

### Nix Integration

The project uses Nix flakes for:
- Dependency management (OpenCV, Boost, Eigen, Google Test)
- Development environment setup
- Reproducible builds across systems

## Testing Strategy

### Unit Tests

- `test_video_loader.cpp`: Tests video loading functionality
- `test_neural_style_transfer.cpp`: Tests style transfer operations
- `test_logger.cpp`: Tests logging functionality

### Test Coverage

Tests cover:
- Successful operations with valid inputs
- Error handling with invalid inputs
- Edge cases and boundary conditions
- File I/O operations

## Dependencies

### Core Dependencies

- **OpenCV 4.x**: Video processing and computer vision
- **Eigen3**: Linear algebra operations
- **Boost**: Program options, filesystem, system utilities

### Development Dependencies

- **Google Test**: Unit testing framework
- **CMake 3.25+**: Build system
- **GCC 13+ or Clang 17+**: C++23 compiler support

## C++23 Features Used

The project leverages modern C++23 features:
- Module system (future implementation)
- Improved constexpr support
- Enhanced template features
- Better type deduction

## Neural Style Transfer Algorithm

### Current Implementation

The current implementation provides a framework for neural style transfer with:
- Style image loading and preprocessing
- Frame-by-frame processing pipeline
- Placeholder style transfer (to be enhanced)

### Future Enhancements

Planned improvements include:
- Deep learning model integration
- GPU acceleration support
- Multiple style algorithms
- Real-time processing optimization

## Performance Considerations

### Memory Management

- RAII principles for resource management
- Smart pointers for automatic memory management
- Efficient OpenCV Mat operations

### Processing Optimization

- Frame-by-frame processing to manage memory
- Configurable processing parameters
- Progress reporting for long operations

## Development Workflow

### Setting Up Development Environment

1. Install Nix package manager
2. Clone the repository
3. Run `nix develop` to enter development shell
4. Build with CMake

### Building and Testing

```bash
# Configure and build
mkdir build && cd build
cmake ..
make -j$(nproc)

# Run tests
ctest --verbose

# Run application
./src/video_styler --help
```

### Adding New Features

1. Design the feature interface
2. Implement the feature with unit tests
3. Update documentation
4. Test with example videos
5. Submit pull request

## Troubleshooting

### Common Issues

1. **CMake Configuration Errors**
   - Ensure all dependencies are available in Nix environment
   - Check C++23 compiler support

2. **OpenCV Linking Issues**
   - Verify OpenCV installation in Nix environment
   - Check pkg-config setup

3. **Test Failures**
   - Ensure test media files can be created
   - Check file permissions in test directory

### Debug Build

For debugging, use:
```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
gdb ./src/video_styler
```

## Contributing

See the main README.md for contribution guidelines and project structure information.
