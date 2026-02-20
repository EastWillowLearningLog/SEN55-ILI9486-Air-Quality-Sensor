# Purpose
Standardize time management across the application to improve testability and decouple core logic from platform-specific APIs.

# Requirements

## ADDED Requirements

### Requirement: Abstract Time Provider
The system SHALL use an abstract `TimeProvider` interface for all time-dependent logic to allow for testability.

#### Scenario: Production runtime
- **WHEN** the application is running on hardware or in the standard PC emulator
- **THEN** it uses the `SystemTimeProvider` which proxies to the platform's native millisecond counter (`millis()` or equivalent)

#### Scenario: Test runtime
- **WHEN** the application is running in the unit test suite
- **THEN** it uses the `MockTimeProvider` which allows tests to explicitly control the passage of time
