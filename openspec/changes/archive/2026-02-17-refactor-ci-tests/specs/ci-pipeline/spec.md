## ADDED Requirements

### Requirement: Independent Test Pipeline
The CI/CD test workflow must be able to build and run tests using the standalone test configuration.

#### Scenario: Running Tests in CI
- **WHEN** The tests workflow is triggered in GitHub Actions
- **THEN** The workflow configures CMake directly from the `tests` subdirectory
- **AND** The build completes successfully without requiring the main project build
- **AND** All tests execute and pass

### Requirement: Backward Compatibility
The main project build must continue to work with tests as a subdirectory.

#### Scenario: Building from Root
- **WHEN** A developer runs `cmake -S . -B build` from the project root
- **THEN** The main project and all subdirectories (including tests) are configured
- **AND** Running `ctest` executes all tests successfully
