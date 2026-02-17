## Why

Current test organization mixes unit tests and integration-style tests in the root `tests/` directory (e.g., `emulator_test.cpp` containing CoreLib unit tests), leading to confusing CI/CD configuration and "organizational debt" that makes it harder to scale the test suite.

## What Changes

- **REORGANIZE**: Move `tests/emulator_test.cpp` to `tests/unit/emulator_test.cpp`.
- **REORGANIZE**: Enforce `tests/integration/` as the exclusive home for visual regression and end-to-end tests.
- **MODIFICATION**: Update `tests/CMakeLists.txt` to register tests based on their directory category.
- **MODIFICATION**: Update `.github/workflows/tests.yml` to specifically target unit tests.
- **MODIFICATION**: Update `.github/workflows/integration-test.yml` to specifically target integration tests.

## Capabilities

### New Capabilities
- `test-infrastructure-separation`: Defines the hierarchical organization of tests into unit/ and integration/ folders with corresponding CMake and CI/CD logical separation.

### Modified Capabilities
- `display-integration-test`: Update requirements to strictly differentiate from unit tests and ensure path consistency.
- `github-workflow-configuration`: Update workflow requirements to reflect the directory-based separation of test types.

## Impact

- **Tests Hierarchy**: New folder structure under `tests/`.
- **CMake**: Changes to `tests/CMakeLists.txt`.
- **CI/CD**: Changes to `.github/workflows/tests.yml` and `.github/workflows/integration-test.yml`.
