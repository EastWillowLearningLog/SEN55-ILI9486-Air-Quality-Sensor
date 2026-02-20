## ADDED Requirements

### Requirement: Abstract Time Provider
The system SHALL use an abstract `TimeProvider` interface for all time-dependent logic to allow for testability.

#### Scenario: Production runtime
- **WHEN** the application is running on hardware or in the standard PC emulator
- **THEN** it uses the `SystemTimeProvider` which proxies to the platform's native millisecond counter (`millis()` or equivalent)

#### Scenario: Test runtime
- **WHEN** the application is running in the unit test suite
- **THEN** it uses the `MockTimeProvider` which allows tests to explicitly control the passage of time

## MODIFIED Requirements

### Requirement: Non-Blocking State Transitions
The system SHALL use a timestamp-based, non-blocking check for button debouncing to prevent UI hangs, utilizing the injected `TimeProvider`.

#### Scenario: State transition requested within debounce period
- **WHEN** a state transition is requested and the time provided by `TimeProvider` since the last transition is less than 200ms
- **THEN** the system ignores the request

#### Scenario: State transition requested after debounce period
- **WHEN** a state transition is requested and the time provided by `TimeProvider` since the last transition is greater than or equal to 200ms
- **THEN** the system processes the request and updates the last transition time

#### Scenario: Clock rollover during debounce period
- **WHEN** the system clock (via `TimeProvider`) rolls over after a state transition
- **THEN** the system correctly calculates the time elapsed using unsigned integer arithmetic and handles the debounce period accurately
