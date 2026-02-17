# Documentation Update Summary: Emulator Testing Architecture

**Date**: 2026-02-17  
**Context**: Documented the new two-tier emulator testing strategy following creation of `emulator.yml` workflow

---

## What Changed

We clarified that the emulator testing has been split into two distinct capabilities:

1. **Smoke Testing** (`emulator.yml`) - *Implemented*
2. **Integration Testing** (`integration-test.yml`) - *Planned*

This separation enables fast crash detection while preserving the option for slower, more thorough visual regression testing.

---

## Documentation Updates

### ✅ Created New Specs

#### 1. `openspec/specs/display-integration-test/spec.md` (NEW)
Comprehensive specification for the planned visual regression testing capability.

**Key Requirements**:
- Checkpoint-based screenshot capture via GTest/GMock
- Deterministic rendering (fixed sensor data, timestamps, animations)
- Reference image storage in Git (`tests/integration/reference_screenshots/`)
- ImageMagick-based pixel comparison with configurable thresholds
- CI artifact upload on regression detection
- Independent workflow execution

**Architecture Notes**:
- Multiple checkpoints per test run (vs single final frame in smoke test)
- Programmatic control through GTest framework
- Distinction from smoke test clearly documented

---

### ✅ Updated Existing Specs

#### 2. `openspec/specs/emulator-split/spec.md` (ENHANCED)
Clarified that this capability is focused on **smoke testing** (execution validation).

**Changes**:
- Added "Overview" section explaining smoke test purpose
- Distinguished from `display-integration-test`
- Added "CI Smoke Test Workflow" requirement
- Added "Screenshot Artifact Preservation" requirement
- Added comparison table: smoke test vs integration test
- Documented `emulator.yml` workflow details

**Key Clarifications**:
- Validates "can it run?" not "does it render correctly?"
- Screenshot is debugging artifact, not regression test assertion
- Fast execution (~5s) for quick feedback

---

#### 3. `openspec/specs/project-overview.md` (UPDATED)
Expanded CI/CD feature list to include emulator testing.

**Before**:
- Generic "automated pipelines for Arduino, PC, WASM"

**After**:
- Arduino compilation verification
- PC builds and unit tests
- **Emulator smoke testing (execution validation)**
- **Display integration tests (visual regression) - Planned**
- WASM deployment to GitHub Pages

---

#### 4. `openspec/specs/software-architecture.md` (ENHANCED)
Added comprehensive "Testing Strategy" section.

**New Content**:
- Testing pyramid diagram showing three tiers
- Detailed description of each test category:
  1. Unit Tests (component isolation)
  2. Emulator Smoke Test (crash detection)
  3. Display Integration Tests (visual regression)
  4. Platform Verification (Arduino/WASM)
- Testing principles:
  - Deterministic execution
  - Independent workflows
  - Artifact preservation
  - Separation of concerns

**Visual Comparison Table**:
| Category | Purpose | Speed | CI Workflow | Spec |
|----------|---------|-------|-------------|------|
| Unit Tests | Component isolation | ~10s | tests.yml | ci-pipeline/spec.md |
| Smoke Test | Execution validation | ~5s | emulator.yml | emulator-split/spec.md |
| Integration Test | Visual regression | ~30s+ | integration-test.yml (future) | display-integration-test/spec.md |

---

#### 5. `README.md` (ENHANCED)
Transformed emulator documentation from simple usage guide to comprehensive testing overview.

**Changes**:
- **Added**: CI status badges for all four workflows (Arduino, Tests, Emulator, WASM)
- **Added**: Project title header
- **Restructured**: "Emulator Testing" section with three subsections:
  1. Interactive Mode (local development)
  2. Test Mode (CI smoke test)
  3. Integration Testing (planned)
- **Clarified**: Smoke test purpose and limitations
- **Referenced**: OpenSpec documentation for integration test details

**Key Improvements**:
- Users can see CI status at a glance
- Clear distinction between smoke test and integration test
- Forward reference to planned capabilities

---

## Testing Architecture Overview

```
┌─────────────────────────────────────────────────────────┐
│                   Testing Strategy                      │
├─────────────────────────────────────────────────────────┤
│                                                         │
│  Fast Feedback (Parallel Execution)                    │
│  ┌──────────────┐  ┌──────────────┐                    │
│  │  Unit Tests  │  │ Smoke Test   │                    │
│  │  ~10 seconds │  │  ~5 seconds  │                    │
│  │              │  │              │                    │
│  │ Component    │  │ Execution    │                    │
│  │ correctness  │  │ validation   │                    │
│  └──────────────┘  └──────────────┘                    │
│                                                         │
│  Slower, Thorough Validation                           │
│  ┌──────────────────────────────┐                      │
│  │  Integration Tests (Planned) │                      │
│  │  ~30+ seconds                 │                      │
│  │                               │                      │
│  │  Visual regression detection  │                      │
│  └──────────────────────────────┘                      │
│                                                         │
└─────────────────────────────────────────────────────────┘
```

---

## Key Design Decisions Captured

### 1. Reference Image Storage: Git-based (Option A)
- ✅ Reference screenshots committed to `tests/integration/reference_screenshots/`
- ✅ Versioned alongside code
- ✅ Easy to update when UI intentionally changes
- ⚠️  Binary files in Git (acceptable for small BMP files)

### 2. Image Comparison: ImageMagick
- ✅ Industry-standard tool
- ✅ Generates visual diff images
- ✅ Configurable pixel difference thresholds
- 📦 Requires CI dependency installation

### 3. Checkpoint Control: GTest/GMock
- ✅ Programmatic control over emulator execution
- ✅ Can capture screenshots at arbitrary points
- ✅ Deterministic test execution
- 🔧 Requires emulator to expose test hooks

### 4. Deterministic Test Mode Requirements
When `--test` mode is active:
- ✅ Fixed sensor data (seeded/mocked)
- ✅ Fixed timestamps (no wall clock dependency)
- ✅ Fixed animation states (seeded RNG or no randomness)
- 🎯 Guarantees pixel-perfect reproducibility

### 5. Workflow Independence
- ✅ Smoke test and integration test run in parallel
- ✅ Faster CI feedback (no blocking dependencies)
- ⚠️  Potential redundant work if both would fail on same issue (acceptable tradeoff)

---

## Next Steps (Out of Scope for This Update)

The following are documented as planned but not yet implemented:

### Implementation Tasks (Future)
1. **Emulator Test Hooks**
   - Add GTest integration to DisplayEmulator
   - Expose checkpoint trigger API
   - Implement multi-screenshot capture

2. **Reference Screenshot Generation**
   - Run emulator in deterministic mode locally
   - Validate output is correct
   - Commit initial reference images to `tests/integration/reference_screenshots/`

3. **Integration Test Workflow**
   - Create `.github/workflows/integration-test.yml`
   - Install ImageMagick in CI
   - Implement comparison logic with thresholds
   - Configure artifact upload on failure

4. **Deterministic Mode Implementation**
   - Ensure sensor mocks use fixed data
   - Replace `time()` calls with injectable clock
   - Seed or eliminate animation randomness

---

## Files Modified

```
openspec/specs/
├── display-integration-test/
│   └── spec.md                    ← NEW: Integration test requirements
├── emulator-split/
│   └── spec.md                    ← ENHANCED: Smoke test clarification
├── project-overview.md            ← UPDATED: CI/CD feature list
└── software-architecture.md       ← ENHANCED: Testing strategy section

README.md                           ← ENHANCED: Badges + testing docs
```

---

## Verification Checklist

- ✅ Emulator smoke test purpose clearly documented
- ✅ Integration test capability fully specified
- ✅ Distinction between smoke and integration tests explained
- ✅ CI/CD pipelines enumerated in project overview
- ✅ Testing strategy added to architecture docs
- ✅ README updated with badges and clear usage guide
- ✅ Forward references to planned capabilities documented
- ✅ Design decisions captured (storage, tools, control mechanism)
- ✅ Deterministic testing requirements specified

---

## Documentation Quality

All specs follow OpenSpec Gherkin-style format:
- `GIVEN`, `WHEN`, `THEN`, `AND` scenario structure
- Clear requirement statements
- Explicit validation criteria
- Visual diagrams where helpful
- Comparison tables for clarity

---

**Status**: Documentation complete. Ready for implementation when reference screenshots are available.
