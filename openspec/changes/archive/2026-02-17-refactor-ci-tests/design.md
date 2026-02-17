## Context
Currently, the `tests` directory is not a standalone CMake project. It relies on the root `CMakeLists.txt` for configuration context and uses `file(COPY ...)` to move test resources, which fails when building `tests` in isolation. The goal is to decouple this dependency to allow for modular builds and faster test execution.

## Goals / Non-Goals
**Goals:**
- Make `tests/CMakeLists.txt` a fully independent CMake configuration.
- detailed CI/CD workflows that test this independent build capability.
- Ensure tests can locate resources (e.g., reference images) without relying on build-time file copying that assumes a specific directory layout.

**Non-Goals:**
- Refactoring the entire project structure beyond the test dependencies.
- Changing the testing framework (GoogleTest) itself.

## Decisions
1.  **Remove `file(COPY)`**: We will remove the `file(COPY reference ...)` command from `tests/CMakeLists.txt`.
2.  **Compile Definitions for Paths**: We will inject the absolute path to the reference images directory using `target_compile_definitions`. The test code will use this definition (`TEST_RESOURCE_DIR`) to locate images at runtime.
    ```cmake
    target_compile_definitions(tests PRIVATE TEST_RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/reference")
    ```
3.  **CI Workflow Update**: We will update `.github/workflows/tests.yml` to specifically target the `tests` directory for configuration and building, proving its independence.
4.  **Root Build Integration**: The root `CMakeLists.txt` will still `add_subdirectory(tests)`, but the `tests` configuration will be robust enough to handle both standalone and subdirectory modes.

## Risks / Trade-offs
- **Path Handling**: ensuring the compile definition works correctly across different environments (local vs CI).
- **Complexity**: Slightly more complex C++ code to handle the path construction, but significantly cleaner build system.
