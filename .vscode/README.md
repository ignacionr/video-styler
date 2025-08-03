# VS Code CMake Tools with Nix

Unfortunately, VS Code's CMake Tools extension has difficulty working directly with Nix environments because it tries to use system tools instead of the Nix-provided ones.

## Recommended Workflow

### Option 1: Use VS Code Tasks (Recommended)
1. Use `Ctrl+Shift+P` (Cmd+Shift+P on Mac) → "Tasks: Run Task"
2. Select "Configure CMake (Ninja)" to configure the project
3. Select "Build Debug (Ninja)" to build the project
4. Select "Run Tests (Ninja)" to run tests

### Option 2: Use Integrated Terminal
1. Open the integrated terminal in VS Code (`Ctrl+`` `)
2. The terminal is configured to use the Nix environment automatically
3. Run the standard build commands:
   ```bash
   mkdir -p build && cd build
   cmake -GNinja ..
   ninja
   ./tests/video_styler_tests
   ```

### Option 3: Manual CMake Tools Setup
If you really want to use CMake Tools extension:

1. Clean your build directory: `rm -rf build`
2. Open a terminal in the Nix environment: `nix develop`
3. In that terminal, start VS Code: `code .`
4. This will inherit the Nix environment in CMake Tools

## Testing
The best approach for running tests is to use the VS Code tasks or the terminal:
```bash
nix develop --command bash -c "cd build && ./tests/video_styler_tests"
```

## IntelliSense
IntelliSense should work correctly once the project is built, as it will use the generated `compile_commands.json` file.
