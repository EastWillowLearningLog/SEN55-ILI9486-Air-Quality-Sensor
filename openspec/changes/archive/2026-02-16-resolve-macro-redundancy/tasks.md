# Tasks: Resolve Macro Redundancy

## 1. Clean up LCD_GUI.cpp

- [x] 1.1 Remove lines 18-24 (local `DEBUG` definition block)
- [x] 1.2 Add `#include "Debug.h"` at the top of `src/Display/LCD_GUI.cpp`

## 2. Verify Compatibility

- [x] 2.1 Audit all `DEBUG(...)` calls in `LCD_GUI.cpp` to ensure they use a single argument
- [x] 2.2 Toggle `DEV_DEBUG` in `Debug.h` to verify global control works (if environment allows compilation)

## 3. Archive

- [x] 3.1 Run `openspec archive` to complete the change record
