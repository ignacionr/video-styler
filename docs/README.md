# Documentation

This directory contains architecture diagrams and technical documentation for the Video Styler project.

## Architecture Diagram

### Files
- `architecture.dot` - Source file in DOT format (Graphviz)
- `architecture.png` - Generated PNG diagram (included in main README)

### Regenerating the Diagram

To update the architecture diagram:

1. Edit `architecture.dot` with your changes
2. Regenerate the PNG:
   ```bash
   nix develop --command dot -Tpng docs/architecture.dot -o docs/architecture.png
   ```

### Diagram Contents

The architecture diagram shows:
- **Core modules**: Video Processor, Neural Style Transfer, Utilities
- **External dependencies**: OpenCV, Eigen, Boost
- **Build system**: CMake, Nix environment
- **Testing framework**: Google Test with CTest integration
- **Data flow**: Input videos → processing → stylized output
- **Development tools**: VS Code integration and debugging

### Adding New Components

When adding new architectural components:
1. Update the DOT file with new nodes and relationships
2. Regenerate the PNG diagram
3. Update the README architecture section if needed
4. Consider adding to the class hierarchy documentation
