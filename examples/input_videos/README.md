# Place your input video files here

This directory should contain sample input videos for testing the Video Styler application.

Example files you might add:
- `sample_short.mp4` - A short test video (10-30 seconds)
- `sample_medium.mp4` - A medium test video (1-2 minutes)
- `sample_long.mp4` - A longer test video (5+ minutes)

## Recommended Properties

- **Resolution**: 720p or 1080p for good quality/performance balance
- **Duration**: Start with shorter videos for faster testing
- **Format**: MP4 with H.264 encoding
- **Frame Rate**: 24, 25, or 30 FPS

## Creating Test Videos

You can create simple test videos using FFmpeg:

```bash
# Create a 10-second test video with moving colored rectangles
ffmpeg -f lavfi -i testsrc=duration=10:size=1280x720:rate=30 -c:v libx264 sample_test.mp4

# Create a video from images
ffmpeg -framerate 30 -pattern_type glob -i '*.jpg' -c:v libx264 output.mp4
```
