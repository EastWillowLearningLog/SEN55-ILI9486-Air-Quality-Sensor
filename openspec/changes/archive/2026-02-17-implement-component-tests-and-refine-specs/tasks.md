## 1. Refactor App to Expose State for Testing

- [x] 1.1 Move `AppState` enum and `currentState` variable to a header or provide `App_GetState()` getter in `App.cpp` to allow verification in tests.
- [x] 1.2 Identify and export button coordinate macros if not already available in `App.h`.

## 2. Implement Interaction Unit Tests

- [x] 2.1 Update `tests/emulator_test.cpp` to include a test case for "Main to Info" screen transition using `SDL_SetMouseState`.
- [x] 2.2 Update `tests/emulator_test.cpp` to include a test case for "Info to Main" screen transition.
- [x] 2.3 Verify transitions work correctly with simulated 200ms debounce delay.

## 3. Implement Data Edge-Case Tests

- [x] 3.1 Update `tests/emulator_test.cpp` to include a test case that injects `NaN` values for VOC/NOx indices.
- [x] 3.2 Verify that the UI logic (specifically labels) handles `NaN` without crashing or displaying incorrect strings.

## 4. Finalize Project Specs

- [x] 4.1 Sync the Test Responsibility Matrix from the delta spec to the main system specs.
- [x] 4.2 Verify all tests follow the new redundancy-avoidance guidelines.
