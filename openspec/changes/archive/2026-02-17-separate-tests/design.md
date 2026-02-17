## Context

The project currently has a `tests/` directory with a mix of unit tests (`emulator_test.cpp`) at the root and integration tests in an `integration/` subfolder. This design implements a symmetrical structure recommended by team discussion and industry best practices.

## Goals / Non-Goals

**Goals:**
- Implement a clear `tests/unit/` and `tests/integration/` separation.
- Decouple unit test execution from integration test execution in CI.
- Maintain standalone test build capability.

**Non-Goals:**
- Refactoring the internal logic of the tests themselves.
- Adding new test cases (outside of verifying the reorganization).

## Decisions

### 1. Symmetrical Directory Structure
**Decision**: Move `emulator_test.cpp` into `tests/unit/`.
- **Rationale**: Cleans up the `tests/` root and provides a clear place for future unit tests. It aligns with the existing `integration/` folder.
- **Alternatives**:
  - *Keep unit tests at root*: Rejected. Inconsistent and harder to filter in CI.
  - *Move integration tests to root*: Rejected. Integration tests have more dependencies (reference images) and should stay isolated.

### 2. CMake Target Organization
**Decision**: Keep `tests/CMakeLists.txt` central but update it to handle the new paths.
- **Rationale**: Centralizing the configuration for both suites is easier to manage than nested `CMakeLists.txt` files for this size of project, provided paths are handled correctly.
- **Implementation**:
  - Update `add_executable(emulator_test unit/emulator_test.cpp)`.
  - Update `TEST_RESOURCE_DIR` for unit tests if they ever need resources (currently they don't use the `reference` folder, which was a dummy anyway).

### 3. Workflow Specialization
**Decision**: Specifically target the respective targets/folders in GitHub Actions.
- **Rationale**: Prevents redundant test execution and allows faster feedback loops for unit tests.
- **Workflow Changes**:
  - `tests.yml`: Build `emulator_test` target and run `ctest -R EmulatorUnitTest`.
  - `integration-test.yml`: Build `display_integration_test` target and run `ctest -R display_integration`.

## Risks / Trade-offs

- **[Risk] Path Ambiguity** → **[Mitigation]** Use absolute or correctly calculated relative paths in `tests/CMakeLists.txt` (using `${CMAKE_CURRENT_SOURCE_DIR}`).
- **[Risk] CI Redundancy** → **[Mitigation]** Ensure `integration-test.yml` doesn't accidentally run unit tests by using specific `ctest` filters.
