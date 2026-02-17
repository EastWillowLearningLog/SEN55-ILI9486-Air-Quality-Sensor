# Capability: emulator-split

## Overview
The DisplayEmulator provides two execution modes to support both automated CI testing (smoke tests) and interactive development. This capability focuses on **execution validation** - ensuring the emulator can run without crashing in headless CI environments.

**Note**: This is distinct from `display-integration-test`, which performs visual regression testing via screenshot comparison.

## ADDED Requirements

### Requirement: Dual Execution Modes
The emulator must support both automated test mode and interactive development mode.

#### Scenario: Automated Test Mode (Smoke Test)
- **WHEN** the emulator is launched with the `--test` argument
- **THEN** it runs for a fixed number of frames (25)
- **AND** it saves the final screen content to `screenshot.bmp`
- **AND** it terminates automatically with exit code 0 (success)
- **AND** no manual interaction is required

**Purpose**: Validate that the emulator can execute in headless CI environments (xvfb-run) without crashes.

#### Scenario: Interactive Development Mode
- **WHEN** the emulator is launched without arguments
- **THEN** it runs indefinitely until manually closed
- **AND** it accepts and processes mouse/keyboard input for interaction
- **AND** the window remains responsive to user actions

**Purpose**: Enable developers to manually test UI rendering and interactions locally.

---

### Requirement: CI Smoke Test Workflow
The emulator must have an automated CI workflow that validates basic execution.

#### Scenario: Emulator Smoke Test in CI
- **GIVEN** a GitHub Actions workflow (`emulator.yml`)
- **WHEN** code is pushed to main or a PR is opened
- **THEN** the workflow builds the emulator
- **AND** runs it with `xvfb-run ./DisplayEmulator --test`
- **AND** the test passes if exit code is 0
- **AND** on failure, uploads `screenshot.bmp` as an artifact for debugging

**Validation Criteria**:
- ✅ Emulator compiles successfully
- ✅ SDL2 initializes in virtual framebuffer
- ✅ Runs without segfaults or crashes
- ✅ Generates screenshot file
- ❌ Does NOT validate screenshot content (see `display-integration-test`)

---

### Requirement: Screenshot Artifact Preservation
Failed smoke tests must preserve debugging artifacts.

#### Scenario: Debugging Failed Execution
- **GIVEN** the emulator crashes or fails during smoke test
- **WHEN** the CI workflow detects failure
- **THEN** `screenshot.bmp` is uploaded as a GitHub Actions artifact
- **AND** developers can download it to diagnose the issue

---

## Distinction from Integration Tests

| Capability | emulator-split (Smoke Test) | display-integration-test |
|------------|----------------------------|--------------------------|
| **Purpose** | Can it run? | Does it render correctly? |
| **Validation** | Exit code 0 | Pixel-level screenshot comparison |
| **Screenshot Use** | Debugging artifact only | Regression test assertion |
| **CI Workflow** | `emulator.yml` | `integration-test.yml` (future) |
| **Speed** | Fast (~5s) | Slower (~30s+) |
| **Dependencies** | Xvfb, SDL2 | + ImageMagick, GTest, reference images |

---

## CI Workflow Details

### File: `.github/workflows/emulator.yml`
**Name**: Display Emulator CI  
**Triggers**: Push to main, Pull requests  
**Job**: `build-and-run`

**Steps**:
1. Checkout code with submodules
2. Install dependencies: `xvfb`, `libsdl2-dev`, `libsdl2-mixer-dev`, `libgtest-dev`
3. Configure CMake: `cmake ..`
4. Build: `cmake --build .`
5. Run emulator test: `xvfb-run ./DisplayEmulator --test`
6. Upload screenshot on failure

**Success Criteria**: Exit code 0 from step 5
