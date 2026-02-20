## 1. Core Logic Redesign

- [x] 1.1 Add `App_ResetState()` to `App.h` and `App.cpp` for test isolation
- [x] 1.2 Refactor `App_Loop` in `App.cpp` to use non-blocking timing logic with `currentMillis` and `lastTransitionTime`

## 2. Test Updates

- [x] 2.1 Create `tests/unit/debounce_performance_test.cpp` to measure and verify the optimization
- [x] 2.2 Update `tests/unit/emulator_test.cpp` to handle the new timing behavior
- [x] 2.3 Verify unsigned integer arithmetic correctly handles single rollovers in `debounce_performance_test.cpp`
