# GitHub Workflow Configuration

## Purpose

This specification defines the standard configuration requirements for GitHub Actions workflows in the project. It ensures consistent checkout behavior across all CI/CD workflows, particularly regarding submodule handling.
## Requirements
### Requirement: GitHub Actions workflows MUST use checkout with recursive submodules
All GitHub Actions workflows that build or test the project SHALL use `actions/checkout@v4` with `submodules: recursive` configuration to ensure complete repository checkout including all submodule dependencies.

#### Scenario: Workflow checks out repository with submodules
- **WHEN** a GitHub Actions workflow runs that requires the project code
- **THEN** the workflow MUST include a checkout step with `uses: actions/checkout@v4` and `with: submodules: recursive`

#### Scenario: Integration test workflow checks out submodules
- **WHEN** the integration test workflow (`.github/workflows/integration-test.yml`) runs
- **THEN** the workflow MUST check out all submodules recursively before building or testing

#### Scenario: Unit test workflow checks out submodules
- **WHEN** the unit test workflow (`.github/workflows/tests.yml`) runs
- **THEN** the workflow MUST check out all submodules recursively before building or testing

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

