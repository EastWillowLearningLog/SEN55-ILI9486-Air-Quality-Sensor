## Context

The recent `refactor-app-loop-debounce` change improved button debouncing by using timestamps instead of blocking delays. However, to make the debouncing testable, a global `mockMillis` variable was introduced and shared between the application code (`App.cpp`) and the test suite (`debounce_performance_test.cpp`). This tight coupling to a global variable is an anti-pattern that makes time-dependent logic harder to scale and test cleanly.

## Goals / Non-Goals

**Goals:**
- Decouple `App.cpp` from the global `mockMillis` and the system `millis()` function.
- Introduce a `TimeProvider` interface to abstract time retrieval.
- Provide a `SystemTimeProvider` for production use (Arduino or PC).
- Provide a `MockTimeProvider` for unit testing.
- Refactor existing tests to use `MockTimeProvider`.

**Non-Goals:**
- Changing the debounce logic or thresholds themselves.
- Refactoring other sensor mock interfaces (they are already well-abstracted).

## Decisions

1. **`TimeProvider` Interface Definition**
   - Create an abstract class with `virtual unsigned long getMillis() = 0;`.
   - *Rationale:* Standard C++ approach for Dependency Injection, allowing swapping implementations at runtime.

2. **Dependency Injection Method**
   - Pass `TimeProvider*` to `App_Setup` and store it as a static pointer inside `App.cpp` for use by `App_Loop`.
   - *Rationale:* Keeps the function signature of `App_Loop` unchanged, which is called frequently in the main loop, while explicitly requiring the dependency at setup time.

3. **Production Implementation (`SystemTimeProvider`)**
   - Thin wrapper around Arduino `millis()` or a PC equivalent.
   - *Rationale:* Keeps production code simple and isolates platform-specific time API calls.

## Risks / Trade-offs

- **Risk: Virtual Function Overhead** → Using a virtual function for `getMillis()` introduces slight overhead compared to calling `millis()` directly.
  - *Mitigation:* The overhead is negligible for a 1-second UI loop and humans reacting to 200ms debounces. The testability benefits far outweigh this cost.

## Migration Plan
1. Define `TimeProvider` interface in `App.h`.
2. Update `App.cpp` to use it instead of `currentMillis`/`mockMillis`.
3. Update `main_pc.cpp` / `main_arduino.cpp` to inject `SystemTimeProvider`.
4. Update unit tests to use `MockTimeProvider`.
