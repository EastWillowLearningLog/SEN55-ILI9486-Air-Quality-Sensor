## Context

The project uses a tiered testing strategy:
1. **Smoke Tests** (`main_pc.cpp`): Validates the full binary, SDL initialization, and long-running execution stability.
2. **Component Tests** (`tests/emulator_test.cpp`): Should validate discrete logic without binary overhead.

Currently, `emulator_test.cpp` repeats some stability checks from `main_pc.cpp`. We need to pivot it towards interaction and edge-case validation.

## Goals / Non-Goals

**Goals:**
- Implement automated state transition tests using `SDL_SetMouseState`.
- Validate NaN handling in `App.cpp` UI logic.
- Codify the "EastWillow Principles" of testing in the project specifications.

**Non-Goals:**
- Do not repeat "loop N times" stability tests in unit tests.
- Do not add visual regression to unit tests (handled by integration tests).

## Decisions

- **Expose App State**: To verify transitions without brittle side-effect detection, we will move `currentState` from `static` to a member of an `AppInstance` struct or provide a getter if necessary. However, for now, we will try to verify via standard Mock Sensor interactions if possible.
- **Simulated SDL Input**: Use the platform-independent `SDL_SetMouseState` (mocked in `LCD_Driver_SDL.cpp`) to simulate user clicks at specific X/Y coordinates defined in `App.cpp`.
- **NaN Injection**: Temporarily modify `SensorMock` or use a specialized mock to return `NaN` for VOC/NOx indices.

## Risks / Trade-offs

- **Coordinate Fragility**: Tests depend on UI button coordinates. If UI layout changes, tests will break. 
  - *Mitigation*: Use the macros defined in `App.cpp` (e.g., `BTN_INFO_X`) if they can be exposed or mirrored in a shared header.
