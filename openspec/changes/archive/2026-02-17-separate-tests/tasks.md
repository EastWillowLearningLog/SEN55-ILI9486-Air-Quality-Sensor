## 1. Directory Reorganization

- [x] 1.1 Create `tests/unit/` directory
- [x] 1.2 Move `tests/emulator_test.cpp` to `tests/unit/emulator_test.cpp`

## 2. Build System Updates

- [x] 2.1 Update `tests/CMakeLists.txt` to reflect new path for `emulator_test.cpp`
- [x] 2.2 Update `tests/CMakeLists.txt` to ensure `TEST_RESOURCE_DIR` for unit tests is valid (or removed if unused)
- [x] 2.3 Verify `tests` standalone build completes successfully

## 3. CI/CD Specialization

- [x] 3.1 Update `.github/workflows/tests.yml` to specifically build and run unit tests
- [x] 3.2 Update `.github/workflows/integration-test.yml` to specifically build and run integration tests
- [x] 3.3 Ensure consistency in checkout and submodule settings across both workflows

## 4. Verification

- [x] 4.1 Run unit tests locally and verify pass
- [x] 4.2 Run integration tests locally and verify pass
- [x] 4.3 Verify that `tests.yml` does not execute integration tests
