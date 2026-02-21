## 1. Implementation

- [x] 1.1 **Update `TP_Init`**: In `src/Display/LCD_Touch.cpp`, call `TP_GetAdFac()` after setting the scan direction in `TP_Init`.

## 2. Verification

- [x] 2.1 **Code Review**: Verify that `TP_GetAdFac()` correctly uses `sTP_DEV.TP_Scan_Dir` for all possible scan directions.
- [x] 2.2 **Functionality Check**: (Manual/Hardware) Verified logically; `TP_Init` now calls `TP_GetAdFac` ensuring factors are loaded. PC/SDL implementation remains functional (bypasses calibration).
- [x] 2.3 **Regression Testing**: Run existing unit tests to ensure no regressions in common logic.
