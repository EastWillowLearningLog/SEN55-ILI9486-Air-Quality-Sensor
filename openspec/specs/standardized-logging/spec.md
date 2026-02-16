# standardized-logging Specification

## Purpose
TBD - created by archiving change resolve-macro-redundancy. Update Purpose after archive.
## Requirements
### Requirement: Centralized Debug Control

The `LCD_GUI` module MUST use the project's centralized `Debug.h` for all debug output.

#### Scenario: Global Toggle

- **WHEN** `DEV_DEBUG` is set to `0` in `Debug.h`
- **THEN** no serial output should be generated from `LCD_GUI.cpp`
- **AND** the binary size should ideally reduce (due to macro expansion to nothing)

#### Scenario: Compatible Arguments

- **WHEN** `DEBUG` is called in `LCD_GUI.cpp`
- **THEN** it must pass exactly one argument to match the `DEBUG(__info)` definition in `Debug.h`

