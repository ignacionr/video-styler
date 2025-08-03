# Video Styler - Tool Versions and Dependencies

## Current Tool Versions (Updated August 2025)

This document tracks the latest versions of tools and libraries used in the Video Styler project.

### Build System
- **CMake**: 4.0.3 (stable) / 4.1.0-rc4 (release candidate)
  - Minimum required: 3.30 (for latest policy support)
  - Features: Modern CMake practices, enhanced C++23 support

### Compilers
- **LLVM/Clang**: 20.1.0 (released March 4, 2025)
  - Target in Nix: `clang_18` (latest available in nixpkgs)
  - Features: Full C++23 support, latest optimizations
- **GCC**: Alternative compiler option
  - Minimum: GCC 13+ for C++23 support

### Language Standard
- **C++**: C++23 (ISO/IEC 14882:2023)
  - Features used: Modules (experimental), Coroutines, Ranges, Concepts
  - Future: C++26 features will be adopted as they become stable

### Core Libraries

#### Computer Vision
- **OpenCV**: 4.12.0 (released July 9, 2025)
  - Latest features: Enhanced DNN module, improved performance
  - Components: core, imgproc, imgcodecs, videoio, highgui, dnn
  - Backward compatibility: Minimum OpenCV 4.10+

#### Linear Algebra
- **Eigen**: 3.4+ (latest available)
  - High-performance matrix operations
  - Header-only library with vectorization support

#### Utilities
- **Boost**: 1.82+ 
  - Components: system, filesystem, program_options, thread
  - Modern C++ utilities and cross-platform support

### Testing Framework
- **Google Test**: Latest available in nixpkgs
  - Unit testing with modern C++ features
  - Integration with CMake CTest

### Development Tools
- **Ninja**: Build system generator (faster than Make)
- **pkg-config**: Library configuration management
- **LLVM Tools**: Static analysis, formatting, debugging
- **GDB**: Debugging support
- **Doxygen**: Documentation generation

### Package Management
- **Nix**: Reproducible development environment
  - Flake-based configuration
  - Automatic dependency resolution
  - Cross-platform support (Linux, macOS)

## Version Update Strategy

### Major Version Updates
- **CMake**: Update when new LTS versions are released
- **LLVM/Clang**: Follow annual release cycle
- **OpenCV**: Update for new feature releases (4.x series)

### Stability Considerations
- Use stable versions in CI/CD
- Test with latest versions in development
- Maintain backward compatibility for at least 2 major versions

### Nix Package Availability
Some cutting-edge versions may not be immediately available in nixpkgs:
- **Clang 20.x**: May need to wait for nixpkgs update
- **CMake 4.x**: Gradual rollout in package managers
- **OpenCV 4.12**: Usually available within 1-2 months of release

## Performance Optimizations

### Compiler Flags
```bash
# Debug builds
-g -O0 -fsanitize=address,undefined

# Release builds  
-O3 -DNDEBUG -flto -march=native -mtune=native
```

### CMake Optimizations
- Link Time Optimization (LTO) for release builds
- Native CPU optimization flags
- Modern CMake policies for best practices

### C++23 Features Used
- **Modules**: Faster compilation (experimental)
- **Coroutines**: Asynchronous processing
- **Ranges**: Functional programming patterns
- **Concepts**: Better template constraints
- **std::expected**: Error handling without exceptions

## Compatibility Matrix

| Tool/Library | Minimum Version | Recommended | Latest Tested |
|-------------|----------------|-------------|---------------|
| CMake       | 3.30           | 4.0.3       | 4.1.0-rc4     |
| Clang       | 17.0           | 20.1.0      | 20.1.0        |
| OpenCV      | 4.10           | 4.12.0      | 4.12.0        |
| Boost       | 1.80           | 1.82+       | 1.84          |
| Eigen       | 3.4            | 3.4+        | 3.4.0         |

## Migration Notes

### From Older Versions
- **CMake 3.x → 4.x**: New policies, improved C++23 support
- **Clang 17 → 20**: Better C++23 implementation, performance improvements
- **OpenCV 4.10 → 4.12**: New DNN features, API enhancements

### Breaking Changes
- Monitor CMake policy changes in 4.x series
- Test C++23 standard library updates
- Verify OpenCV API compatibility

## Development Environment Setup

1. **Install Nix** (if not already installed)
2. **Enter development environment**:
   ```bash
   nix develop
   ```
3. **Build with latest tools**:
   ```bash
   mkdir -p build && cd build
   cmake -GNinja ..
   ninja
   ```
4. **Run tests**:
   ```bash
   ctest --verbose
   ```

This ensures you're using the latest, well-tested versions of all dependencies.
