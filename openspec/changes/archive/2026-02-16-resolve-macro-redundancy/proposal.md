# Proposal: Resolve Macro Redundancy

## Why

The `LCD_GUI.cpp` file contains a local `DEBUG` macro definition that bypasses the project-wide `Debug.h` configuration. This makes it impossible to disable GUI-related debug logs globally, leading to unnecessary serial output and potential macro conflicts.

## What Changes

- Remove the local `DEBUG` macro definition in `src/Display/LCD_GUI.cpp`.
- Include `Debug.h` in `src/Display/LCD_GUI.cpp` to use the standardized logging mechanism.
- Ensure `DEBUG` calls in `LCD_GUI.cpp` are compatible with the `Debug.h` macro signature (taking a single argument).

## Capabilities

### Modified Capabilities
- `LCD Logging`: Debug logs in the LCD library now respect the global `DEV_DEBUG` flag.

## Impact

- `src/Display/LCD_GUI.cpp`: Logic for debugging replaced with centralized header.
