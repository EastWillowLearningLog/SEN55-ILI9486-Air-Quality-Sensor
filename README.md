Web mockup Display:
https://eastwillowlearninglog.github.io/SEN55-ILI9486-Air-Quality-Sensor/

Software Bill of Materials:
* ILI9486 Driver Form [3.5inch TFT Touch Shield](https://www.waveshare.com/wiki/3.5inch_TFT_Touch_Shield)
* SEN55 Library From [arduino-i2c-sen5x](https://github.com/Sensirion/arduino-i2c-sen5x)
* SEN55 Library Depency From [arduino-core](https://github.com/Sensirion/arduino-core)

Acknowledging AI Usage:
* Code assistance and debugging for the LCD driver and SEN55 implementation provided by Google's Gemini.

### Emulator Usage

The emulator supports two modes of operation:

1.  **Interactive Mode (Default)**:
    Run the emulator without any arguments to start an interactive session. You can interact with the simulated LCD screen using your mouse.
    ```bash
    ./build/DisplayEmulator
    ```

2.  **Test Mode (CI/Automated)**:
    Run the emulator with the `--test` flag. In this mode, it runs for a fixed duration (25 frames), captures the screen content to `screenshot.bmp`, and exits automatically. This is used for automated regression testing.
    ```bash
    ./build/DisplayEmulator --test
    ```
