# Spec Update Summary: Refinements to Smoke Test

**Date**: 2026-02-17 (Second Update)  
**Context**: User refined the smoke test implementation to clarify scope and improve developer experience

---

## Changes Made by User

### 1. README.md - Added Developer Workflows

**Added Local Build Commands**:
```bash
mkdir build
cd build
cmake ..
cmake --build .
./DisplayEmulator
```

**Added Local CI Testing**:
```bash
gh extension install https://github.com/nektos/gh-act
gh act push  # Simulates push event locally
```

**Impact**: Developers can now build/run locally and test CI workflows without pushing to GitHub.

---

### 2. tests/emulator_test.cpp - Removed Visual Regression Test

**Removed**: `OutputMatchesReference` test that compared screenshots against golden reference

**Rationale**: 
- Visual regression testing does not belong in the smoke test suite
- Smoke test should only validate execution (can it run?)
- Screenshot comparison will be implemented in future `integration-test.yml`

**Impact**: Clarifies separation of concerns between smoke and integration testing.

---

### 3. .github/workflows/emulator.yml - Always Upload Screenshots

**Before**:
```yaml
- name: Upload Screenshot (on failure)
  if: failure()
  uses: actions/upload-artifact@v4
  with:
    name: emulator-screenshot-failed
    path: build/screenshot.bmp
```

**After**:
```yaml
- name: Upload Screenshot
  uses: actions/upload-artifact@v4
  with:
    name: emulator-screenshot
    path: build/screenshot.bmp
```

**Changes**:
- Removed `if: failure()` condition → **always uploads**
- Renamed artifact: `emulator-screenshot-failed` → `emulator-screenshot`

**Rationale**:
- Screenshots are useful for **inspection**, not just debugging failures
- Developers can verify emulator rendered something
- Can be used as reference when creating integration tests
- Makes artifact purpose clearer (not just for failures)

---

## Spec Updates Made

### 1. emulator-split/spec.md

#### Changed: Screenshot Artifact Requirement

**Before**: "Screenshot Artifact Preservation" (only on failure)

**After**: "Screenshot Artifact Capture" (always)

**Updated Scenario**:
```gherkin
GIVEN the emulator completes execution (success or failure)
WHEN the CI workflow completes
THEN screenshot.bmp is uploaded as artifact named "emulator-screenshot"
AND developers can download it to:
  - Verify the emulator rendered something
  - Inspect output for obvious rendering issues
  - Use as reference when creating integration tests
```

**Added Note**: "This artifact is for **inspection only**, not automated validation. Visual regression testing will be handled by the `display-integration-test` capability."

---

#### Added: Local Development Workflow Section

**New Content**:
- Building and running locally (CMake commands)
- Testing CI workflows locally (`gh act` usage)
- Explains how to avoid pushing to test CI

---

#### Updated: CI Workflow Details

**Changed Step 6**: "Upload screenshot artifact (always, with name `emulator-screenshot`)"

**Added**: "**Artifacts**: `screenshot.bmp` uploaded for every run (inspection only, not validated)"

---

### 2. display-integration-test/spec.md

#### Added: Context Note

**New Overview Addition**:
> **Context**: This capability is separate from the `emulator-split` smoke test. The smoke test (`emulator.yml`) validates execution only (can it run without crashing?). Visual regression testing (screenshot comparison) was intentionally removed from the smoke test suite and will be implemented here when reference images are available.

**Impact**: Clarifies the intentional separation and explains why visual regression isn't in smoke test.

---

## Architecture Clarification

### Smoke Test Scope (Final)

```
emulator.yml (Smoke Test)
┌──────────────────────────────────────┐
│ Purpose: Execution Validation        │
├──────────────────────────────────────┤
│ ✅ Can it compile?                   │
│ ✅ Can it initialize SDL2?           │
│ ✅ Can it run without crashing?      │
│ ✅ Does it generate output file?     │
│                                      │
│ ❌ Does NOT validate rendering       │
│ ❌ Does NOT compare screenshots      │
│ ❌ Does NOT test visual correctness  │
└──────────────────────────────────────┘

Screenshot Usage: Inspection only
- Verify something was rendered
- Spot obvious rendering issues manually
- Use as baseline for integration tests
```

### Integration Test Scope (Planned)

```
integration-test.yml (Visual Regression)
┌──────────────────────────────────────┐
│ Purpose: Rendering Validation        │
├──────────────────────────────────────┤
│ ✅ Pixel-perfect screenshot comparison │
│ ✅ Multi-checkpoint validation       │
│ ✅ Automated regression detection    │
│ ✅ Diff generation on failure        │
└──────────────────────────────────────┘

Screenshot Usage: Automated validation
- Pixel-level comparison
- Assert against reference images
- Fail on regressions
```

---

## Key Principles Reinforced

1. **Separation of Concerns**
   - Smoke test = "Can it run?"
   - Integration test = "Does it render correctly?"

2. **Artifact Purpose**
   - Smoke test artifacts = Inspection/reference
   - Integration test artifacts = Validation/debugging

3. **Developer Experience**
   - Local build/run commands documented
   - Local CI testing via `gh act`
   - No need to push to test workflows

4. **Testing Philosophy**
   - Fast feedback (smoke test ~5s)
   - Slower validation (integration test ~30s+)
   - Independent workflows (parallel execution)

---

## Files Modified in This Update

```
openspec/specs/
├── emulator-split/spec.md          ← Updated artifact requirement + local workflow
└── display-integration-test/spec.md ← Added context note

.agent/
└── next-steps-integration-testing.md ← NEW: Implementation guide
```

---

## Updated Specs Summary

| Spec | Status | Purpose | CI Workflow |
|------|--------|---------|-------------|
| `emulator-split` | ✅ Implemented | Execution validation | `emulator.yml` |
| `display-integration-test` | 🔮 Specified | Visual regression | `integration-test.yml` (future) |
| `ci-pipeline` | ✅ Documented | Unit test independence | `tests.yml` |

---

## What's Different from First Update

| Aspect | First Update | Second Update |
|--------|-------------|---------------|
| Screenshot Upload | On failure only | **Always** |
| Artifact Name | `emulator-screenshot-failed` | `emulator-screenshot` |
| Visual Regression Test | Existed in `emulator_test.cpp` | **Removed** |
| Local Workflows | Not documented | **Added to README + spec** |
| Purpose Clarity | Good | **Crystal clear** |

---

## Developer-Facing Improvements

1. **Clearer Purpose**: Smoke test scope is now unambiguous
2. **Better DX**: Local build and CI testing commands readily available
3. **Useful Artifacts**: Screenshots always available for inspection
4. **No Confusion**: Visual regression clearly separated from smoke testing

---

**Status**: Specs fully updated to reflect refined smoke test scope. Ready for integration test implementation when needed.
