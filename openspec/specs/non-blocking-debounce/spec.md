## ADDED Requirements

### Requirement: Non-Blocking State Transitions
The system SHALL use a timestamp-based, non-blocking check for button debouncing to prevent UI hangs.

#### Scenario: State transition requested within debounce period
- **WHEN** a state transition is requested and the time since the last transition is less than 200ms
- **THEN** the system ignores the request

#### Scenario: State transition requested after debounce period
- **WHEN** a state transition is requested and the time since the last transition is greater than or equal to 200ms
- **THEN** the system processes the request and updates the last transition time

#### Scenario: Clock rollover during debounce period
- **WHEN** the system clock (`currentMillis`) rolls over after a state transition
- **THEN** the system correctly calculates the time elapsed using unsigned integer arithmetic and handles the debounce period accurately
