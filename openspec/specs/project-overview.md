# Project Overview

## Introduction
A comprehensive air quality monitoring system utilizing the Sensirion SEN55 sensor and an ILI9486-based 3.5" TFT display. The project aims to provide real-time visualization of key air quality metrics including PM1.0, PM2.5, PM4.0, PM10, VOC Index, and NOx Index.

## Target Platforms
- **Embedded**: Arduino Uno (Target Hardware)
- **Simulation**: PC (SDL2-based emulator for development/testing)
- **Web**: Emscripten/WASM (Browser-based demo/simulation)

## Core Features
- **Real-time Monitoring**: Continuous reading of SEN55 environmental data.
- **Data Visualization**: Graphical display of sensor values on ILI9486 TFT.
- **Interactive UI**: Touch screen interaction for page navigation and calibration.
- **Cross-Platform**: Unified codebase supporting embedded hardware and PC/Web simulation.
- **CI/CD**: Automated pipelines for:
  - Arduino compilation verification
  - PC builds and unit tests
  - Emulator smoke testing (execution validation)
  - Display integration tests (visual regression) - *Planned*
  - WASM deployment to GitHub Pages

