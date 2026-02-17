## Why

The current build system tightly couples the `tests` subdirectory with the main project execution logic, preventing `tests` from being built or run independently. Specifically, `tests/CMakeLists.txt` relies on `file(COPY ...)` commands that assume a specific directory structure incompatible with standalone execution. The user desires a modular architecture where each CMake project (main, tests, emulator) can be configured and run independently, allowing for faster development cycles and cleaner CI/CD pipelines.

## What Changes

1.  **Decouple Tests**: Modify `tests/CMakeLists.txt` to remove hardcoded dependencies on the parent project's binary directory structure (specifically the `file(COPY reference ...)` command).
2.  **Standalone Execution**: Ensure the `tests` project can be configured (`cmake -S tests -B build_tests`) and built independently of the root `CMakeLists.txt`.
3.  **Align CI/CD**: Update or verify GitHub Actions workflows (`tests.yml`) to utilize this new standalone capability, ensuring consistent behavior between local development and CI environments.

## Capabilities

### New Capabilities
- `test-independence`: The testing framework will support standalone configuration and execution, allowing tests to run without building the entire firmware application.

### Modified Capabilities
- `ci-pipeline`: The CI/CD pipeline for tests (`tests.yml`) will clearly separate the testing phase from the main firmware build artifact generation.

## Impact

- **Build System**: `tests/CMakeLists.txt` and potentially the root `CMakeLists.txt`.
- **CI/CD**: `.github/workflows/tests.yml`.
- **Developer Workflow**: Developers can run unit tests faster by targeting the `tests` project directly.
