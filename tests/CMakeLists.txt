# Find Google Test
find_package(GTest REQUIRED)
include(GoogleTest)

# Test sources
set(TEST_SOURCES
    test_main.cpp
    test_video_loader.cpp
    test_neural_style_transfer.cpp
    test_logger.cpp
)

# Create test executable
add_executable(video_styler_tests ${TEST_SOURCES})

# Link libraries for tests
target_link_libraries(video_styler_tests
    GTest::gtest
    GTest::gtest_main
    ${OPENCV4_LIBRARIES}
    Eigen3::Eigen
    Boost::system
    Boost::filesystem
    Boost::program_options
)

# Include directories for tests
target_include_directories(video_styler_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

# Add compile definitions for tests
target_compile_definitions(video_styler_tests PRIVATE
    ${OPENCV4_CFLAGS_OTHER}
)

# Add object library for source files (excluding main.cpp)
add_library(video_styler_lib OBJECT
    ${CMAKE_SOURCE_DIR}/src/video_processor/video_loader.cpp
    ${CMAKE_SOURCE_DIR}/src/style_transfer/neural_style_transfer.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/logger.cpp
)

target_include_directories(video_styler_lib PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_compile_definitions(video_styler_lib PRIVATE
    ${OPENCV4_CFLAGS_OTHER}
)

# Link the object library to tests
target_link_libraries(video_styler_tests video_styler_lib)

# Discover tests
gtest_discover_tests(video_styler_tests)
