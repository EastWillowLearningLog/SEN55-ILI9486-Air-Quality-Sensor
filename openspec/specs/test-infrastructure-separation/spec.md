# test-infrastructure-separation Specification

## Purpose
This specification defines the hierarchical organization of tests into unit/ and integration/ folders with corresponding CMake and CI/CD logical separation to ensure scalability and maintainability of the test suite.
## Requirements
### Requirement: Symmetrical Test Folder Hierarchy
The `tests/` directory SHALL be organized into a symmetrical hierarchy consisting of `unit/` and `integration/` subdirectories.

#### Scenario: Unit Test Location
- **WHEN** adding a new unit test for a CoreLib component
- **THEN** it MUST be placed in `tests/unit/`
- **AND** it MUST NOT be placed at the root of `tests/`

#### Scenario: Integration Test Location
- **WHEN** adding a new visual regression or end-to-end test
- **THEN** it MUST be placed in `tests/integration/`

### Requirement: Independent CMake Test Suites
The CMake configuration SHALL define independent test suites for unit and integration tests, allowing them to be built and executed separately.

#### Scenario: Building Unit Tests Only
- **WHEN** running `cmake --build . --target <unit_test_target>`
- **THEN** only the unit test suite and its dependencies are built
- **AND** integration test resources (like reference images) are not required

#### Scenario: Building Integration Tests Only
- **WHEN** running `cmake --build . --target <integration_test_target>`
- **THEN** the integration test suite and its dependencies are built

### Requirement: Categorized CTest Registration
All tests SHALL be registered with CTest using labels or names that allow easy filtering by category.

#### Scenario: Running Only Unit Tests
- **WHEN** running `ctest -R UnitTest` (or similar filter)
- **THEN** only tests in the `unit/` directory are executed

