# Source files
set(SOURCES
    main.cpp
    video_processor/video_loader.cpp
    style_transfer/neural_style_transfer.cpp
    utils/logger.cpp
)

# Create the executable
add_executable(video_styler ${SOURCES})

# Link libraries
target_link_libraries(video_styler
    ${OpenCV_LIBS}
    Eigen3::Eigen
    Boost::system
    Boost::filesystem
    Boost::program_options
)

# Add compile definitions
target_compile_definitions(video_styler PRIVATE
    ${OPENCV4_CFLAGS_OTHER}
)
