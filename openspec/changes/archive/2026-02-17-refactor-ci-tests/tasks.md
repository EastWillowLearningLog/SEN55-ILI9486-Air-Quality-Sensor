## 1. Test Refactoring

- [x] 1.1 Update `tests/emulator_test.cpp` to use the `TEST_RESOURCE_DIR` macro for locating reference images instead of a hardcoded relative path.
- [x] 1.2 Update `tests/CMakeLists.txt` to remove `file(COPY reference ...)` and inject `TEST_RESOURCE_DIR` definition using `target_compile_definitions`.
- [x] 1.3 Update `tests/CMakeLists.txt` to define project and required targets (like `DisplayEmulator`) if built standalone, or use `find_package` / mocks. (Need to ensure `DisplayEmulator` is available to test).

## 2. CI/CD Alignment

- [x] 2.1 Update `.github/workflows/tests.yml` to configure and build from the `tests` subdirectory directly (`cmake -S tests -B build`).
- [x] 2.2 Verify that the main project build (`cmake -S . -B build`) still correctly builds and runs tests via `add_subdirectory(tests)`.
