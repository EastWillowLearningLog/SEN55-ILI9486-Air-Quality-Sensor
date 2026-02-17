# Next Steps: Display Integration Testing Implementation

**Last Updated**: 2026-02-17  
**Status**: Smoke test implemented and documented. Integration test fully specified, awaiting implementation.

---

## ✅ Completed (Smoke Test)

### Implementation
- ✅ `emulator.yml` workflow created and running
- ✅ Emulator `--test` mode implemented (25 frames, screenshot output)
- ✅ CI uploads `screenshot.bmp` as artifact for every run
- ✅ Removed visual regression test from `tests/emulator_test.cpp` (moved to future integration suite)

### Documentation
- ✅ `emulator-split/spec.md` fully documents smoke test requirements
- ✅ `display-integration-test/spec.md` created with integration test specification
- ✅ `project-overview.md` updated with CI/CD pipeline list
- ✅ `software-architecture.md` has testing strategy pyramid
- ✅ `README.md` includes CI badges and testing guide
- ✅ Local development workflow documented (`cmake` build + `gh act` testing)

---

## 🔮 Planned (Integration Test)

The following tasks will enable visual regression testing through multi-checkpoint screenshot comparison.

### Phase 1: Reference Image Generation

**Objective**: Create known-good reference screenshots for comparison.

#### Tasks:
1. **Ensure Deterministic Rendering**
   - Verify sensor mock uses fixed data (no randomness)
   - Replace any `time()` calls with injectable/fixed clock
   - Eliminate or seed any animation randomness
   - Test: Run emulator multiple times, verify screenshots are byte-identical

2. **Generate Reference Screenshots**
   ```bash
   # In local environment
   cd build
   ./DisplayEmulator --test
   # Verify screenshot.bmp looks correct visually
   ```

3. **Commit Reference Images**
   ```bash
   mkdir -p tests/integration/reference_screenshots
   cp build/screenshot.bmp tests/integration/reference_screenshots/golden_screen.bmp
   git add tests/integration/reference_screenshots/golden_screen.bmp
   git commit -m "Add reference screenshot for integration testing"
   ```

4. **Document Reference Update Process**
   - Create `tests/integration/reference_screenshots/README.md`
   - Explain how to update references when UI intentionally changes
   - Document validation process (manual visual inspection)

---

### Phase 2: Emulator Test Hooks (GTest Integration)

**Objective**: Enable programmatic control of emulator for checkpoint-based testing.

#### Tasks:
1. **Refactor Emulator for Testability**
   - Extract main loop into controllable class (e.g., `EmulatorEngine`)
   - Add API for step-by-step execution (`stepFrame()`, `captureScreenshot()`)
   - Allow external control of frame count

2. **Create GTest Integration Test Suite**
   ```cpp
   // tests/integration/display_integration_test.cpp
   class DisplayIntegrationTest : public ::testing::Test {
     protected:
       EmulatorEngine emulator;
       
       void SetUp() override {
         emulator.initialize(/* deterministic config */);
       }
   };
   
   TEST_F(DisplayIntegrationTest, CheckpointStartup) {
     emulator.stepFrames(0);  // Initial state
     emulator.captureScreenshot("checkpoint_startup.bmp");
     CompareWithReference("checkpoint_startup.bmp", "reference_screenshots/startup.bmp");
   }
   
   TEST_F(DisplayIntegrationTest, CheckpointSensors) {
     emulator.stepFrames(10);  // Sensor data displayed
     emulator.captureScreenshot("checkpoint_sensors.bmp");
     CompareWithReference("checkpoint_sensors.bmp", "reference_screenshots/sensors.bmp");
   }
   
   TEST_F(DisplayIntegrationTest, CheckpointFinal) {
     emulator.stepFrames(25);  // Full UI
     emulator.captureScreenshot("checkpoint_final.bmp");
     CompareWithReference("checkpoint_final.bmp", "reference_screenshots/final.bmp");
   }
   ```

3. **Implement Image Comparison Helper**
   ```cpp
   void CompareWithReference(const std::string& actual, const std::string& reference) {
     // Use ImageMagick or simple byte comparison
     // Assert pixel difference < threshold
     // Generate diff.bmp on failure
   }
   ```

---

### Phase 3: CI Integration Test Workflow

**Objective**: Create `.github/workflows/integration-test.yml` to run visual regression tests.

#### Tasks:
1. **Create Workflow File**
   ```yaml
   name: Display Integration Tests
   
   on:
     push:
       branches: [main]
     pull_request:
   
   jobs:
     visual-regression:
       runs-on: ubuntu-latest
       
       steps:
         - name: Checkout code
           uses: actions/checkout@v4
           with:
             submodules: recursive
         
         - name: Install dependencies
           run: |
             sudo apt-get update
             sudo apt-get install -y xvfb libsdl2-dev imagemagick
         
         - name: Configure CMake
           run: cmake -B build -S .
         
         - name: Build
           run: cmake --build build
         
         - name: Run Integration Tests
           run: |
             cd build
             xvfb-run ctest --output-on-failure -R DisplayIntegration
         
         - name: Upload Artifacts on Failure
           if: failure()
           uses: actions/upload-artifact@v4
           with:
             name: integration-test-artifacts
             path: |
               build/checkpoint_*.bmp
               build/diff_*.bmp
   ```

2. **Test Locally with `gh act`**
   ```bash
   gh act push -W .github/workflows/integration-test.yml
   ```

3. **Verify CI Badge**
   - Add to README.md after workflow is merged
   ```markdown
   [![Integration Tests](https://github.com/eastwillowlearninglog/SEN55-ILI9486-Air-Quality-Sensor/actions/workflows/integration-test.yml/badge.svg)](...)
   ```

---

### Phase 4: Optional Enhancements

#### Advanced Comparison
- Implement pixel difference threshold per checkpoint
- Generate HTML diff reports with side-by-side comparison
- Add comparison metadata (% difference, affected regions)

#### Baseline Management
- PR workflow to auto-update references on approval
- Tag-based reference versioning
- Automated visual diff comments on PRs

#### Cross-Platform Testing
- Run integration tests on macOS/Windows runners
- Detect platform-specific rendering bugs

---

## Current Architecture

```
Testing Tiers (Current State)
┌────────────────────────────────────────┐
│  ✅ Smoke Test (emulator.yml)         │
│     • Can it run?                      │
│     • Exit code 0 validation           │
│     • Screenshot for inspection        │
│     • ~5 seconds                       │
├────────────────────────────────────────┤
│  🔮 Integration Test (planned)        │
│     • Does it render correctly?        │
│     • Pixel-level comparison           │
│     • Multi-checkpoint validation      │
│     • ~30+ seconds                     │
└────────────────────────────────────────┘
```

---

## Key Decisions Captured

| Decision | Choice | Status |
|----------|--------|--------|
| **Screenshot Upload** | Always (not just on failure) | ✅ Implemented |
| **Visual Regression in Smoke Test** | Removed (moved to integration) | ✅ Cleaned up |
| **Reference Storage** | Git-based in `tests/integration/reference_screenshots/` | 🔮 Specified |
| **Comparison Tool** | ImageMagick `compare -metric AE` | 🔮 Specified |
| **Test Control** | GTest/GMock programmatic control | 🔮 Specified |
| **CI Independence** | Smoke and integration run in parallel | 🔮 Specified |
| **Local Testing** | `gh act` for CI simulation | ✅ Documented |

---

## When to Start Phase 1

**Prerequisites**:
- ✅ Smoke test stable and passing
- ✅ Specs documented
- ✅ Development workflow established

**Ready to Start When**:
- You have time to validate reference screenshots
- You're ready to refactor emulator for testability
- Integration testing becomes a priority

**Estimated Effort**:
- Phase 1 (References): ~2 hours
- Phase 2 (GTest Hooks): ~4-6 hours
- Phase 3 (CI Workflow): ~2 hours
- **Total**: ~8-10 hours of development time

---

## Questions Before Starting

Before implementing integration tests, consider:

1. **How many checkpoints do you need?**
   - Single final frame (simplest)
   - Startup + Final (reasonable)
   - Startup + Mid + Final (comprehensive)

2. **How strict should comparison be?**
   - Byte-identical (strict, may break on trivial changes)
   - Pixel threshold ~100 (allows minor anti-aliasing variations)
   - Percentage-based ~1% (more forgiving)

3. **How will you handle reference updates?**
   - Manual commit after visual validation
   - Automated PR workflow
   - Both (manual for main, automated for branches)

---

**Status**: All specs updated. Ready for implementation when you are!
