## ADDED Requirements

### Requirement: default-calibration-loading
The touch panel initialization MUST load default calibration factors to ensure the touch screen is usable immediately after boot.

#### Scenario: initialization-loads-factors
- **WHEN** `TP_Init` is called.
- **THEN** it MUST set the scanning direction.
- **AND** it MUST call `TP_GetAdFac()` to load the corresponding default scaling factors and offsets.
