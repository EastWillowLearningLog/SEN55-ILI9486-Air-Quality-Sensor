## Why

The current `TP_Init` function in `src/Display/LCD_Touch.cpp` initializes the touch scanning direction but neglects to call `TP_GetAdFac()`. This means the touch panel starts with uninitialized or incorrect calibration factors and offsets, resulting in inaccurate touch coordinate mapping until a manual calibration (`TP_Adjust`) is performed.

## What Changes

Update `TP_Init` in `src/Display/LCD_Touch.cpp` to call `TP_GetAdFac()` immediately after setting the `sTP_DEV.TP_Scan_Dir`. This ensures that default calibration parameters are automatically loaded upon initialization.

## Capabilities

### Modified Capabilities
- `touch-initialization`: Update requirement to ensure default calibration factors are loaded during initialization to provide immediate touch accuracy.

## Impact

- **Touch Accuracy**: Immediate functionality of the touch screen with default parameters.
- **Code Maintenance**: Aligns initialization with expected state for touch coordinate calculation in `TP_Scan`.
- **User Experience**: Removes the necessity for immediate manual calibration in standard deployment scenarios.
