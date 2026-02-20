#include <climits>
#include <cmath>
#include <gtest/gtest.h>

// CoreLib component headers
#include "App.h"
#include "LCD_Driver_SDL.h"
#include "SensorMock.h"

class DebouncePerformanceTest : public ::testing::Test {
protected:
  void SetUp() override {
    SDL_SetMouseState(0, 0, false);
    App_ResetState();
  }

  void TearDown() override {
    // Cleanup if needed
  }
};

/**
 * Test: Debounce Optimization
 * Validates that App_Loop doesn't block for 200ms when handling touch events.
 * It checks that after a click, subsequent clicks within 200ms are ignored,
 * but App_Loop returns immediately.
 */
TEST_F(DebouncePerformanceTest, NonBlockingDebounce) {
  SensorMock sensor;
  MockTimeProvider timeProvider;
  App_Setup(&sensor, &timeProvider);

  // Initial state should be MAIN
  EXPECT_EQ(App_GetState(), APP_STATE_MAIN);

  // 1. Click INFO button (BTN_INFO_X, BTN_INFO_Y)
  SDL_SetMouseState(BTN_INFO_X + 5, BTN_INFO_Y + 5, true);

  // Measure how many mockMillis pass during App_Loop
  unsigned long startMillis = timeProvider.getMillis();
  App_Loop(&sensor); // Should detect press and switch state
  timeProvider.advance(
      50); // Simulate the fact that App_Loop took some ms (although we removed
           // the internal advance, we expect it to return fast)
  unsigned long elapsed = timeProvider.getMillis() - startMillis;

  // The loop itself advances mockMillis by 50ms.
  // We expect it NOT to block for an extra 200ms.
  EXPECT_EQ(App_GetState(), APP_STATE_INFO);
  EXPECT_LE(elapsed, 100)
      << "App_Loop blocked too long, potentially still using delay";

  SDL_SetMouseState(BTN_INFO_X + 5, BTN_INFO_Y + 5, false);
  App_Loop(&sensor);

  // 2. Click BACK button immediately (debounce active)
  SDL_SetMouseState(BTN_BACK_X + 5, BTN_BACK_Y + 5, true);
  App_Loop(&sensor); // This should be ignored due to debounce

  EXPECT_EQ(App_GetState(), APP_STATE_INFO)
      << "State transitioned during debounce period";

  // Advance mockMillis to simulate time passing beyond debounce period
  timeProvider.advance(200);

  // 3. Click BACK button again after debounce period
  App_Loop(&sensor);

  EXPECT_EQ(App_GetState(), APP_STATE_MAIN)
      << "State failed to transition after debounce period";
}

/**
 * Test: Unsigned Integer Arithmetic Rollover
 * Validates that the debounce logic correctly handles a clock rollover.
 */
TEST_F(DebouncePerformanceTest, ClockRollover) {
  SensorMock sensor;
  MockTimeProvider timeProvider;
  App_Setup(&sensor, &timeProvider);

  // Set mockMillis near max unsigned long value to trigger a rollover
  timeProvider.set(ULONG_MAX - 100);

  // Let initial debounce period (-200 initialization) pass
  timeProvider.advance(200);

  // 1. Click INFO button
  SDL_SetMouseState(BTN_INFO_X + 5, BTN_INFO_Y + 5, true);
  App_Loop(&sensor); // This sets lastTransitionTime = mockMillis which is
                     // ULONG_MAX - 50

  EXPECT_EQ(App_GetState(), APP_STATE_INFO);

  SDL_SetMouseState(0, 0, false);
  App_Loop(&sensor);

  // Now mockMillis will have rolled over
  timeProvider.advance(50);
  App_Loop(&sensor);
  timeProvider.advance(50);
  App_Loop(&sensor);
  timeProvider.advance(50);
  App_Loop(&sensor);
  timeProvider.advance(50);
  App_Loop(&sensor);
  // Total added: ~ 200ms

  // The expression (currentMillis - lastTransitionTime) should correctly yield
  // ~200. 149 - (ULONG_MAX - 50) = 149 - (-51) = 200.

  // 2. Click BACK button and verify it transitions, proving the formula works
  SDL_SetMouseState(BTN_BACK_X + 5, BTN_BACK_Y + 5, true);
  App_Loop(&sensor);

  EXPECT_EQ(App_GetState(), APP_STATE_MAIN)
      << "Rollover prevented state transition";
}
