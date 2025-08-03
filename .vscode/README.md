# VS Code Integration with Nix Environment

This document explains how to work with VS Code when using the Nix development environment.

## VS Code Test Explorer Setup ✅

The VS Code Test Explorer is now configured to work with our Nix environment! Here's what I've set up:

### Installed Extensions
- **C++ TestMate** - Provides Google Test integration with VS Code Test Explorer

### Configuration
- Test executable wrapper: `build/tests/video_styler_tests_nix`
- This wrapper automatically runs tests in the correct Nix environment
- Tests will appear in the VS Code Test Explorer panel (beaker icon on the left sidebar)

### How to Use the Test Explorer
1. **Build the project first** using the VS Code task or terminal
2. **Open the Test Explorer** by clicking the beaker (🧪) icon in the left sidebar
3. **Discover tests** - TestMate should automatically find your tests
4. **Run tests** individually or in groups by clicking the play buttons
5. **Debug tests** by right-clicking and selecting "Debug Test"

### Test Explorer Features
- ✅ Individual test execution
- ✅ Test group execution  
- ✅ Test results with pass/fail indicators
- ✅ Test output and logs
- ✅ Debug support with breakpoints
- ✅ Test filtering and search

## Alternative Testing Methods

### Option 1: Use VS Code Tasks (Also Available)
1. Use `Ctrl+Shift+P` (Cmd+Shift+P on Mac) → "Tasks: Run Task"
2. Select from these available tasks:
   - **"Configure CMake (Ninja)"** - Configure the project
   - **"Build Debug (Ninja)"** - Build the project
   - **"Run Tests"** - Run all unit tests 
   - **"Build and Test"** - Full configure + build + test cycle

### Option 2: Use Integrated Terminal
1. Open terminal in VS Code (`Ctrl+`` or `Cmd+`` `)
2. Run standard commands:
   ```bash
   nix develop
   mkdir -p build && cd build
   cmake -GNinja ..
   ninja
   ./tests/video_styler_tests
   ```

## Troubleshooting

### If tests don't appear in Test Explorer:
1. Ensure the project is built: Run "Build Debug (Ninja)" task
2. Check that `build/tests/video_styler_tests_nix` exists and is executable
3. Refresh the Test Explorer (click the refresh button)
4. Check the Output panel → "C++ TestMate" for any error messages

### If tests fail to run:
1. Verify the Nix environment is working: `nix develop --command echo "OK"`
2. Test the wrapper manually: `./build/tests/video_styler_tests_nix --gtest_list_tests`
3. Ensure all dependencies are available in the Nix environment

### CMake Tools Integration Note
VS Code's CMake Tools extension may have difficulty with the Nix environment. For best results:
- Use the VS Code tasks for building
- Use the Test Explorer for running tests
- If you need CMake Tools, start VS Code from within `nix develop`

## IntelliSense
IntelliSense works correctly once the project is built, using the generated `compile_commands.json` file.
