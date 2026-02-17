## MODIFIED Requirements

### Requirement: Consistency across workflow files
All workflow files that require source code SHALL use the same checkout configuration and follow the directory-based separation of test categories.

#### Scenario: Unit test workflow checks out submodules
- **WHEN** the unit test workflow (`.github/workflows/tests.yml`) runs
- **THEN** it MUST check out all submodules recursively
- **AND** it MUST only build and execute tests from the `tests/unit/` suite

#### Scenario: Integration test workflow checks out submodules
- **WHEN** the integration test workflow (`.github/workflows/integration-test.yml`) runs
- **THEN** it MUST check out all submodules recursively
- **AND** it MUST only build and execute tests from the `tests/integration/` suite
