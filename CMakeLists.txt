cmake_minimum_required(VERSION 3.30)  # Updated for latest CMake 4.x features compatibility

# Set C++ standard to C++23 before project declaration
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable latest CMake policies
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.30")
    cmake_policy(SET CMP0167 NEW)  # Latest policy updates
endif()

project(VideoStyler
    VERSION 0.1.0
    DESCRIPTION "Neural Style Transfer for Videos using C++23"
    LANGUAGES CXX
)

# Set build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Compiler-specific options for latest toolchains
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        -march=native
        -mtune=native
        # C++23 specific optimizations
        -fcoroutines-ts  # Enable coroutines
        -fmodules-ts     # Enable modules (experimental)
    )
    
    # Enable latest sanitizers for Debug builds
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g -O0 -fsanitize=address,undefined)
        add_link_options(-fsanitize=address,undefined)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(-O3 -DNDEBUG -flto)  # Link Time Optimization
        add_link_options(-flto)
    endif()
endif()

# Find required packages - Updated for latest versions
find_package(PkgConfig REQUIRED)

# OpenCV 4.12+ with latest features
find_package(OpenCV 4.10 REQUIRED COMPONENTS core imgproc imgcodecs videoio highgui dnn)
if(OpenCV_FOUND)
    message(STATUS "Found OpenCV version: ${OpenCV_VERSION}")
    if(OpenCV_VERSION VERSION_GREATER_EQUAL "4.12")
        message(STATUS "Using latest OpenCV 4.12+ features")
        add_compile_definitions(OPENCV_LATEST_FEATURES)
    endif()
endif()

# Fallback to pkg-config if find_package fails
if(NOT OpenCV_FOUND)
    pkg_check_modules(OPENCV4 REQUIRED opencv4)
endif()

find_package(Eigen3 3.4 REQUIRED)  # Latest Eigen3
find_package(Boost 1.82 REQUIRED COMPONENTS system filesystem program_options thread)  # Latest Boost

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${OPENCV4_INCLUDE_DIRS})

# Add subdirectories
add_subdirectory(src)

# Enable testing
enable_testing()
add_subdirectory(tests)

# Install configuration
install(TARGETS video_styler
    RUNTIME DESTINATION bin
)

# CPack configuration for packaging
set(CPACK_PACKAGE_NAME "VideoStyler")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
set(CPACK_GENERATOR "TGZ")
include(CPack)
