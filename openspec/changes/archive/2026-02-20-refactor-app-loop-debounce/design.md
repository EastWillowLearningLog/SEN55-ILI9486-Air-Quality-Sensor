## Context

The `App_Loop` function previously used `Driver_Delay_ms(200)` for button debouncing. This blocked the entire application for 200ms every time a state transition occurred, creating significant interaction latency and preventing background processing during that time. Our goal is to replace this blocking delay with a non-blocking timeout check.

## Goals / Non-Goals

**Goals:**
- Eliminate the 200ms blocking delay in `App_Loop`.
- Implement a non-blocking debounce strategy using `lastTransitionTime` and `currentMillis`.
- Maintain correct state transition rules without regressions.
- Allow for test isolation of the `App` component by introducing `App_ResetState()`.

**Non-Goals:**
- Refactoring the entire application state machine.
- Changing the underlying driver delay implementation for other uses.
- Modifying the visual UI components during this change.

## Decisions

1. **Non-blocking Debounce via Timestamps**
   - We use the system's `Driver_GetMillis()` (or a test mock equivalent) to track the time of the last valid state transition (`lastTransitionTime`). On subsequent loop iterations, transitions are ignored until `currentMillis - lastTransitionTime` exceeds the 200ms debounce threshold.
   - *Alternative Considered*: Hardware timers for debouncing. Selected timestamp tracking because it's simpler, cross-platform (works on PC emulator), and doesn't tie up a hardware interrupt.

2. **Test Isolation Support (`App_ResetState`)**
   - Added a new function `App_ResetState()` to clear internal static state (like `lastTransitionTime` or current UI state) between unit test runs.
   - *Alternative Considered*: Exposing internal variables to tests. Selected a dedicated reset function to maintain encapsulation while enabling reliable tests.

## Risks / Trade-offs

- **Risk: Clock Rollover** → The `Driver_GetMillis()` function might roll over after ~49 days (for a 32-bit millisecond counter).
  - *Mitigation*: Unsigned integer arithmetic (`currentMillis - lastTransitionTime > 200`) correctly handles single rollovers.

## Migration Plan
- Deploy changes to `App.cpp` and `App.h`.
- Update the PC emulator test suite and unit test suite to account for the new non-blocking behavior.
