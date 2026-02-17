## ADDED Requirements

### Requirement: Programmatic Touch Simulation
The test environment MUST allow for simulating touch events at specific pixel coordinates to exercise UI interaction logic.

#### Scenario: Simulating a Click on the Info Button
- **WHEN** `SDL_SetMouseState(x, y, true)` is called with coordinates inside the INFO button bounds
- **AND** `App_Loop()` is executed
- **THEN** The application state MUST transition to `APP_STATE_INFO`

### Requirement: Interactive UI Validation
The UI logic MUST be verifiable by observing state changes or specific function calls after simulated interactions.

#### Scenario: Returning from Info Screen
- **WHEN** Current state is `APP_STATE_INFO`
- **AND** A touch event is simulated on the BACK button
- **THEN** The application state MUST transition back to `APP_STATE_MAIN`
