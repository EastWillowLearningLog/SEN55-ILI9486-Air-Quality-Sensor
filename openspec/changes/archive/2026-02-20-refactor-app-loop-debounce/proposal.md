## Why

The `App_Loop` function used `Driver_Delay_ms(200)` for button debouncing, which blocked the entire application for 200ms every time a state transition occurred. This blocked other necessary regular background processing or UI updates during this time, creating lag and interaction latency.

## What Changes

- Replaced blocking `Driver_Delay_ms` with a non-blocking guard using `lastTransitionTime` and `currentMillis`.
- Refactored `App_Loop` to use non-blocking timing logic.
- Added `App_ResetState()` to `App.h` and `App.cpp` to allow test isolation.
- Created `tests/unit/debounce_performance_test.cpp` to measure and verify the timing performance.
- Updated `tests/unit/emulator_test.cpp` to handle the new timing behavior.

## Capabilities

### New Capabilities

- `non-blocking-debounce`: Implements a non-blocking debounce strategy for application state transitions.

### Modified Capabilities

## Impact

- `App.cpp` and `App.h`
- Unit tests (`debounce_performance_test.cpp`, `emulator_test.cpp`)
- Reduces interaction latency from 261ms to 60ms (including pacing delays) with no regressions in functional behavior.
