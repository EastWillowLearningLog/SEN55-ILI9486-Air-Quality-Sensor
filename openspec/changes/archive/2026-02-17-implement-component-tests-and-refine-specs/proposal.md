## Why

The current testing infrastructure has a "smoke test" harness in `main_pc.cpp` that validates execution stability, but lacks granular component-level tests for interactive logic (state transitions) and data edge cases (NaN handling). Furthermore, we need to formalize the testing responsibility matrix to avoid redundancy between smoke tests and unit tests, as discovered during the development of CoreLib components.

## What Changes

- Add interaction tests to `tests/emulator_test.cpp` to verify screen transitions (MAIN ↔ INFO) via simulated touch events.
- Add data integrity tests to verify the UI handles `NaN` values from sensors (warmup state) correctly.
- Update global specifications to establish a Test Responsibility Matrix, ensuring clear separation of concerns between stability-focused smoke tests and logic-focused unit tests.

## Capabilities

### New Capabilities
- `interaction-testing`: Ability to programmatically simulate touch events and verify app state transitions in the emulator environment.

### Modified Capabilities
- `test-independence`: Update requirements to include the Test Responsibility Matrix and explicit guidelines to avoid redundancy with smoke tests.

## Impact

- `tests/emulator_test.cpp`: Will contain new GTest cases for state transitions and NaN handling.
- `openspec/specs/test-independence/spec.md`: Will be updated with the Test Responsibility Matrix.
- `src/App/App.cpp`: Might need minor adjustment (e.g., exposing `currentState` for testing) but ideally will be tested via observed side effects if possible.
