## 1. Setup

## 1. Setup

- [x] 1.1 Add `TimeProvider` interface and implementations (`SystemTimeProvider`, `MockTimeProvider`) to `App.h`
- [x] 1.2 Implement the providers in `App.cpp`

## 2. Core Refactoring

- [x] 2.1 Update `App_Setup` signature to accept `TimeProvider*` and store it internally
- [x] 2.2 Update `App_Loop` to use the injected `TimeProvider` instead of `mockMillis`/`millis()`
- [x] 2.3 Remove the global `mockMillis` and `lastTransitionTime` (make it tied to the App state or static internal)

## 3. Integration Updates

- [x] 3.1 Update `src/main_pc.cpp` to create and inject `SystemTimeProvider`
- [x] 3.2 Update `src/main_arduino.cpp` to create and inject `SystemTimeProvider`
- [x] 3.3 Update `tests/unit/emulator_test.cpp` to create and inject `MockTimeProvider`
- [x] 3.4 Update `tests/unit/debounce_performance_test.cpp` to create and inject `MockTimeProvider` and use `MockTimeProvider::advance()` instead of modifying `mockMillis` directly
