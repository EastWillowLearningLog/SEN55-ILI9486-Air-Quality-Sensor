## MODIFIED Requirements

### Requirement: Test Responsibility Matrix
Tests MUST adhere to the following responsibility hierarchy to prevent redundant coverage and CI bloat.

| Category | Primary Metric | Target Harness |
| :--- | :--- | :--- |
| **Stability** | Uptime, Memory, Platform Init | Smoke/Integration (`main_pc.cpp`) |
| **Interaction** | Finite State Machine transitions | Unit (`emulator_test.cpp`) |
| **Data Integrity** | Edge cases (NaN, Overflow) | Unit (`emulator_test.cpp`) |

#### Scenario: Categorizing a New Test
- **WHEN** A developer adds a test for periodic sensor updates (every 1000ms)
- **THEN** This test MUST reside in the Smoke harness as a stability check
- **AND** It MUST NOT be duplicated in component unit tests.

#### Scenario: Categorizing a NaN Handling Test
- **WHEN** A developer adds a test for UI display during sensor warmup (NaN values)
- **THEN** This test MUST reside in the Component unit tests
- **AND** It uses mocks to inject specific data values.
