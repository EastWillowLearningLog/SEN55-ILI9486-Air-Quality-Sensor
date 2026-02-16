# Hardware Specification

## Overview
Detailed hardware configuration for the Air Quality Monitor.

## Components

### Microcontroller
- **Model**: Arduino Uno (Target platform)
- **MCU**: ATmega328P
- **Clock**: 16 MHz
- **Logic Level**: 5V

### Sensor (SEN55)
- **Model**: Sensirion SEN55
- **Parameters**: PM1.0, PM2.5, PM4.0, PM10, VOC Index, NOx Index
- **Interface**: I2C
- **Address**: 0x69 (Default)
- **Power**: 5V

### Display (ILI9486)
- **Model**: 3.5" TFT LCD Shield
- **Driver**: ILI9486
- **Resolution**: 480x320 pixels
- **Interface**: SPI (4-wire mode via main SPI pins or bit-banged)
- **Backlight**: PWM Control

### Touch Controller
- **Type**: Resistive Touch Panel (4-wire)
- **Interface**: SPI-like Protocol (Often bit-banged or shared SPI bus on shields) 
- **Controller**: Generic Resistive Controller (ADC based, e.g., XPT2046 compatible)

## Pinout Configuration (Arduino Uno Shield)

| Component | Pin Name | Arduino Pin | Function |
|-----------|----------|-------------|----------|
| **Display** | LCD_CS | D10 | Chip Select |
| | LCD_RST | D8 | Reset |
| | LCD_DC | D7 | Data/Command |
| | LCD_BL | D9 | Backlight (PWM) |
| | MOSI | D11 | SPI Data Out |
| | MISO | D12 | SPI Data In |
| | SCK | D13 | SPI Clock |
| **Touch** | TP_CS | D4 | Touch CS |
| | TP_IRQ | D3 | Touch Interrupt |
| | TP_BUSY | D6 | Touch Busy Signal |
| **Sensor** | SDA | A4 | I2C Data |
| | SCL | A5 | I2C Clock |
| **Power** | VCC | 5V | Logic Power |
| | GND | GND | Ground |

## Power Requirements
- **Input Voltage**: 7-12V DC (Barrel Jack) or 5V USB
- **Current Consumption**: estimated 300-500mA (Display backlight + Sensor fan/laser)
