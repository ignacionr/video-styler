cmake_minimum_required(VERSION 3.29)  # Updated for latest CMake 4.x features compatibility

# Set C++23 standard (use c++2b for Clang 16)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Ensure CMake uses the right flag for Clang 16
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2b")
endif()

# Enable latest CMake policies
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.30")
    cmake_policy(SET CMP0167 NEW)  # Latest policy updates
endif()

project(VideoStyler
    VERSION 0.1.0
    DESCRIPTION "Neural Style Transfer for Videos using C++23"
    LANGUAGES CXX
)

# Use modern C++23 features
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Disable dependency scanning for C++20 modules since it's broken with Nix
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

# Add C++23 flag for Clang 16 compatibility
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2b")
endif()

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
        -march=native
        -mtune=native
    )
    
    # Enable debugging for Debug builds only (no sanitizers for initial testing)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g -O0)
        # add_link_options(-fsanitize=address,undefined)  # Temporarily disabled for initial testing
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(-O3 -DNDEBUG -flto)  # Link Time Optimization
        add_link_options(-flto)
    endif()
endif()

# Find required packages - Updated for latest versions
find_package(PkgConfig REQUIRED)

# OpenCV 4.12+ with latest features
find_package(OpenCV 4.9 REQUIRED)
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
if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
else()
    include_directories(${OPENCV4_INCLUDE_DIRS})
endif()

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
