# Examples Directory

This directory contains example input videos, style images, and output results for the Video Styler application.

## File Structure

- `input_videos/` - Sample input videos for testing
- `style_images/` - Sample style images for neural style transfer
- `outputs/` - Generated output videos (created by the application)

## Usage

To test the application with these examples:

```bash
# Build the application first
mkdir build && cd build
cmake ..
make

# Run with example files
./src/video_styler \
    --input ../examples/input_videos/sample.mp4 \
    --style ../examples/style_images/starry_night.jpg \
    --output ../examples/outputs/stylized_video.mp4 \
    --verbose
```

## Adding Your Own Examples

1. Place input videos in the `input_videos/` directory
2. Place style images in the `style_images/` directory
3. The application will create output videos in the `outputs/` directory

## Supported Formats

### Video Formats
- MP4 (recommended)
- AVI
- MOV
- MKV

### Image Formats
- JPEG/JPG (recommended)
- PNG
- BMP
- TIFF

## Notes

- Large video files may take significant processing time
- Style images work best when they have clear artistic patterns
- Output quality depends on the input video resolution and style image quality
