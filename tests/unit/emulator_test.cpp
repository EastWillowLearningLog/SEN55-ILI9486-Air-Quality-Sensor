#include <cmath>
#include <gtest/gtest.h>

// CoreLib component headers
#include "App.h"
#include "DEV_Config.h"
#include "LCD_Driver_SDL.h"
#include "SensorMock.h"

/**
 * Component tests for CoreLib
 *
 * These tests validate CoreLib components directly by linking the library
 * and calling functions, rather than spawning the DisplayEmulator binary.
 */

class CoreLibTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Reset mouse state before each test
    SDL_SetMouseState(0, 0, false);
  }

  void TearDown() override {
    // Reset delay callback
    SetDriverDelayCallback(nullptr);
  }
};

/**
 * Test: SensorMock initialization
 * Validates that the mock sensor can be initialized without errors.
 */
TEST_F(CoreLibTest, SensorMockInitializes) {
  SensorMock sensor;
  uint16_t result = sensor.begin();

  // begin() should return 0 on success (standard error code convention)
  EXPECT_EQ(result, 0) << "SensorMock initialization failed";
}

/**
 * Test: App State Transitions
 * Validates that the app switches between MAIN and INFO screens via touch.
 */
TEST_F(CoreLibTest, InteractionTransitions) {
  SensorMock sensor;
  App_Setup(&sensor);

  // Initial state should be MAIN
  EXPECT_EQ(App_GetState(), APP_STATE_MAIN);

  // 1. Click INFO button (BTN_INFO_X, BTN_INFO_Y)
  SDL_SetMouseState(BTN_INFO_X + 5, BTN_INFO_Y + 5, true);
  App_Loop(&sensor); // Detect press
  SDL_SetMouseState(BTN_INFO_X + 5, BTN_INFO_Y + 5, false);
  App_Loop(&sensor); // Process state change

  EXPECT_EQ(App_GetState(), APP_STATE_INFO)
      << "Failed to transition to INFO screen";

  // 2. Click BACK button (BTN_BACK_X, BTN_BACK_Y)
  SDL_SetMouseState(BTN_BACK_X + 5, BTN_BACK_Y + 5, true);
  App_Loop(&sensor); // Detect press
  SDL_SetMouseState(BTN_BACK_X + 5, BTN_BACK_Y + 5, false);
  App_Loop(&sensor); // Process state change

  EXPECT_EQ(App_GetState(), APP_STATE_MAIN)
      << "Failed to transition back to MAIN screen";
}

/**
 * Test: Button Press Timing
 * Validates that the visual feedback delay (100ms) and debounce delay (200ms)
 * occur in the correct order.
 */
TEST_F(CoreLibTest, ButtonPressTiming) {
  SensorMock sensor;
  App_Setup(&sensor);

  static std::vector<unsigned long> delays;
  delays.clear();

  SetDriverDelayCallback([](unsigned long ms) { delays.push_back(ms); });

  // Click INFO button
  SDL_SetMouseState(BTN_INFO_X + 5, BTN_INFO_Y + 5, true);
  App_Loop(&sensor);

  // We expect:
  // 1. 100ms delay for visual feedback
  // 2. 200ms delay for debounce
  // Note: There might be other delays (e.g. 50ms loop delay if mocked), but
  // typically loop delay is at end. Let's check the sequence contains 100 then
  // 200.

  bool foundFeedback = false;
  bool foundDebounce = false;

  for (size_t i = 0; i < delays.size(); ++i) {
    if (!foundFeedback && delays[i] == 100) {
      foundFeedback = true;
      // Debounce must come AFTER feedback
      for (size_t j = i + 1; j < delays.size(); ++j) {
        if (delays[j] == 200) {
          foundDebounce = true;
          break;
        }
      }
      break;
    }
  }

  EXPECT_TRUE(foundFeedback) << "Did not detect 100ms visual feedback delay";
  EXPECT_TRUE(foundDebounce) << "Did not detect 200ms debounce delay";
}

/**
 * Test: Handle NaN Values
 * Validates that the app handles NaN sensor data (e.g. during warmup) without
 * crashing.
 */
class NaNSensorMock : public SensorMock {
public:
  uint16_t readMeasuredValues(float &pm1p0, float &pm2p5, float &pm4p0,
                              float &pm10p0, float &humidity,
                              float &temperature, float &vocIndex,
                              float &noxIndex) override {
    pm1p0 = 10.0f;
    pm2p5 = 10.0f;
    pm4p0 = 10.0f;
    pm10p0 = 10.0f;
    humidity = 50.0f;
    temperature = 25.0f;
    vocIndex = NAN; // Inject NaN
    noxIndex = NAN; // Inject NaN
    return 0;
  }
};

TEST_F(CoreLibTest, HandleNaNValues) {
  NaNSensorMock nanSensor;
  App_Setup(&nanSensor);

  // Force a sensor update (needs > 1000ms, loops are 50ms each)
  for (int i = 0; i < 25; i++) {
    App_Loop(&nanSensor);
  }

  // If we reached here without crash, the NaN handling in App_Loop is working.
  // The logic in App.cpp (lines 278-291) handles the display strings.
  SUCCEED();
}

/**
 * Test: App_Setup executes without crash
 * Validates that app initialization completes successfully.
 */
TEST_F(CoreLibTest, AppSetupExecutes) {
  SensorMock sensor;
  sensor.begin();

  // App_Setup should not crash when called with valid sensor
  EXPECT_NO_THROW({ App_Setup(&sensor); })
      << "App_Setup threw exception or crashed";
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
