# Design: Standardized Logging in LCD_GUI

## Context

`LCD_GUI.cpp` has a manual `#define DEBUG Serial.print` which is inconsistent with the rest of the project. The project uses `src/Display/Debug.h` which defines a `DEBUG` macro controlled by `DEV_DEBUG`.

## Goals / Non-Goals

**Goals:**
- Unify logging mechanism.
- Allow global disabling of debug strings.

**Non-Goals:**
- Redefining the `DEBUG` macro signature in `Debug.h`.
- Modifying `App.cpp` raw `Serial` calls (out of scope for this specific change).

## Decisions

### Decision 1: Use `Debug.h` Include

We will remove the local `#ifdef ARDUINO ... #define DEBUG ... #endif` block and replace it with `#include "Debug.h"`.

### Decision 2: Handle Argument Differences

The current local `DEBUG` allows `DEBUG("Direct strings")`. The `Debug.h` version is `DEBUG(__info)`, which is compatible with single-argument calls. We will verify all existing calls match this.
