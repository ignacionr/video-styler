# Examples Directory

This directory contains example input videos, style images, and output results for the Video Styler application.

## Directory Structure

### input_videos/
Sample input videos for testing the Video Styler application.

**Recommended files to add:**
- `sample_short.mp4` - A short test video (10-30 seconds)
- `sample_medium.mp4` - A medium test video (1-2 minutes)  
- `sample_long.mp4` - A longer test video (5+ minutes)

**Recommended properties:**
- **Resolution**: 720p or 1080p for good quality/performance balance
- **Duration**: Start with shorter videos for faster testing
- **Format**: MP4 with H.264 encoding
- **Frame Rate**: 24, 25, or 30 FPS

### style_images/
Style images for neural style transfer applications.

**Example style types:**
- `starry_night.jpg` - Van Gogh's famous painting style
- `the_scream.jpg` - Munch's expressive style
- `abstract_art.jpg` - Modern abstract patterns
- `watercolor.jpg` - Watercolor painting style
- `oil_painting.jpg` - Traditional oil painting style

**Recommended properties:**
- **Resolution**: 512x512 to 1024x1024 pixels
- **Format**: JPEG or PNG
- **Quality**: High quality, clear artistic patterns
- **Content**: Strong artistic style, good contrast and color

### outputs/
Generated output videos (created automatically by the application).

**File naming convention:**
- `input_name_style_name.mp4`
- `landscape_starry_night_style.mp4`
- `portrait_watercolor_style.mp4`

**Output properties:**
- Same resolution as input video
- Same frame rate as input video
- Same duration as input video
- Applied style transfer effects

## Usage

To test the application with these examples:

```bash
# Build the application first
nix develop
mkdir -p build && cd build
cmake -GNinja ..
ninja

# Run with example files
./src/video_styler \
    --input ../examples/input_videos/sample.mp4 \
    --style ../examples/style_images/starry_night.jpg \
    --output ../examples/outputs/stylized_video.mp4 \
    --verbose
```

## Creating Test Content

### Generate Test Videos with FFmpeg
```bash
# Create a simple test video (colorful moving pattern)
ffmpeg -f lavfi -i testsrc=duration=10:size=1280x720:rate=30 \
       -c:v libx264 -pix_fmt yuv420p sample_short.mp4

# Create a test video from images
ffmpeg -framerate 30 -pattern_type glob -i '*.jpg' \
       -c:v libx264 -pix_fmt yuv420p output.mp4
```

### Finding Good Style Images
- Famous paintings (Van Gogh, Picasso, Monet)
- Abstract art with strong patterns
- Texture images (marble, wood grain, fabric)
- High-contrast artwork
- Images with distinctive color palettes

## Supported Formats

### Video Formats
- **MP4** (recommended) - Best compatibility
- **AVI** - Standard format
- **MOV** - Apple format
- **MKV** - Open standard format

### Image Formats  
- **JPEG/JPG** (recommended) - Good compression, wide support
- **PNG** - Lossless, transparency support
- **BMP** - Uncompressed
- **TIFF** - High quality

## Performance Notes

- **Large videos**: May take significant processing time depending on length and resolution
- **Style images**: Work best with clear artistic patterns and good contrast
- **Output quality**: Depends on input video resolution and style image quality
- **Processing time**: Roughly 1-10 seconds per frame depending on resolution and hardware

## Tips for Best Results

1. **Start small**: Use short, low-resolution videos for initial testing
2. **High-quality styles**: Use clear, high-resolution style images
3. **Consistent lighting**: Input videos with good, consistent lighting work better
4. **Strong styles**: Bold artistic styles transfer more effectively than subtle ones
5. **Test parameters**: Experiment with different style transfer parameters for optimal results
