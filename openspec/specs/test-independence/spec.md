## ADDED Requirements

### Requirement: Standalone Test Execution
The `tests` CMake project must be configurable and buildable independently from the main project.

#### Scenario: Running Tests from Subdirectory
- **WHEN** A developer navigates to the `tests` directory and runs `cmake -S . -B build`
- **THEN** CMake successfully configures the project without errors related to parent scope variables or missing targets.
- **AND** Running `cmake --build build` compiles the test executable.
- **AND** Running `ctest` executes the tests successfully.

### Requirement: Resource Independence
Tests must locate necessary resources (e.g., reference images) relative to the test executable or source directory, without relying on `file(COPY)` commands that assume a specific build artifact structure from the parent project.

#### Scenario: Verify Resource Loading
- **WHEN** Tests are executed from the build directory.
- **THEN** The test runner correctly locates `reference/` images required for visual regression tests.
