## Why

The current debounce implementation (`refactor-app-loop-debounce`) introduced `mockMillis` as a global variable shared directly between `App.cpp` and `debounce_performance_test.cpp`. This tightly couples the application logic to the test environment and prevents clean simulation of time passing. Abstracting the time provider behind an interface allows for proper Dependency Injection and makes time-dependent logic fully testable without global state hacks.

## What Changes

- Create a `TimeProvider` interface with a `getMillis()` method.
- Create `SystemTimeProvider` for production (using Arduino `millis()` or PC equivalent).
- Create `MockTimeProvider` for testing (allowing tests to manually `advance()` time).
- Refactor `App_Setup` and/or `App_Loop` to accept a `TimeProvider` dependency.
- Update `App.cpp` to use the injected provider instead of `mockMillis` / `millis()`.
- **BREAKING**: Function signatures for `App_Setup` and `App_Loop` will change to accept the new dependency.

## Capabilities

### New Capabilities
- `time-management`: Provides an abstracted interface for time retrieval, allowing for system and mock implementations.

### Modified Capabilities
- `non-blocking-debounce`: Update tests to use `MockTimeProvider` instead of manipulating `mockMillis` directly.

## Impact

- `App.h` and `App.cpp` (signature changes, logic update)
- `tests/unit/debounce_performance_test.cpp` (use mock provider)
- `tests/unit/emulator_test.cpp` (use mock provider)
- `src/main_pc.cpp` and `src/main_arduino.cpp` (inject system provider)
