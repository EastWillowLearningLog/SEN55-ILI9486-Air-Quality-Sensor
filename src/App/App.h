#ifndef APP_H
#define APP_H

#include "../Sensor/SensorIntf.h"

// Define App States
enum AppState { APP_STATE_MAIN, APP_STATE_INFO, APP_STATE_CHART };

// Button Coordinates
#define BTN_INFO_X 400
#define BTN_INFO_Y 10
#define BTN_INFO_W 70
#define BTN_INFO_H 30

// Trend Button (Left of Info Button)
#define BTN_TREND_X 320
#define BTN_TREND_Y 10
#define BTN_TREND_W 70
#define BTN_TREND_H 30

#define BTN_BACK_X 10
#define BTN_BACK_Y 280
#define BTN_BACK_W 70
#define BTN_BACK_H 30

// Chart Configuration
#ifdef ARDUINO
// Reduced size for Arduino due to RAM constraints (2KB)
// 50 points * 2 bytes = 100 bytes
#define CHART_MAX_POINTS 50
#else
// PC can handle more
#define CHART_MAX_POINTS 200
#endif

// Exposed for testing/reset if needed
void App_ResetChartData();

void App_Setup(SensorIntf *sensor);
void App_Loop(SensorIntf *sensor);
AppState App_GetState(void);

#endif
