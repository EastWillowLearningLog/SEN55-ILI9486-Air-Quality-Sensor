## Context

In the current implementation of `src/Display/LCD_Touch.cpp`, the `TP_Init` function only sets the scan direction:
```cpp
void TP_Init( LCD_SCAN_DIR Lcd_ScanDir )
{
  TP_CS_1;

  sTP_DEV.TP_Scan_Dir = Lcd_ScanDir;

  TP_Read_ADC_XY(&sTP_DEV.Xpoint, &sTP_DEV.Ypoint);
}
```
The coordinate transformation logic in `TP_Scan` relies on `sTP_DEV.fXfac`, `sTP_DEV.fYfac`, `sTP_DEV.iXoff`, and `sTP_DEV.iYoff`. These variables are only populated in `TP_Adjust` (manual calibration) or `TP_GetAdFac` (default values). Without calling `TP_GetAdFac` in `TP_Init`, these values remain unitialized (or zero), making the touch panel unusable immediately after boot.

## Goals / Non-Goals

**Goals:**
- Ensure default calibration factors are loaded during touch panel initialization.
- Maintain compatibility with manual calibration (`TP_Adjust`).

**Non-Goals:**
- Implement any persistent storage for calibration (e.g., EEPROM).
- Change the existing calibration algorithm.

## Decisions

- **Call `TP_GetAdFac` in `TP_Init`**: This is the most direct way to ensure the device has working calibration factors on startup. 
- **Sequence**: Call `TP_GetAdFac` after `sTP_DEV.TP_Scan_Dir = Lcd_ScanDir;` since `TP_GetAdFac` uses `sTP_DEV.TP_Scan_Dir` to decide which constants to load.

## Risks / Trade-offs

- **Risk**: If the hardware deviates significantly from the "default" hardware used for these constants, the touch might still be slightly off, but it will be significantly better than zero-initialized factors.
- **Trade-off**: Minimal footprint increase for a significant usability improvement.
