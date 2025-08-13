# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is an Arduino-based RC crawler accessory controller using PlatformIO and the Arduino framework. The project runs on an Arduino Nano 33 BLE board and provides multiple functions for RC car control including:

- **Inclinometer**: Measures pitch and roll using LSM9DS1 sensor with sound warnings
- **Winch Control**: PWM-based motor control with enable/disable functionality  
- **Speed Measurement**: Hall sensor-based speed and distance tracking with flash storage
- **Front Dig**: Servo-controlled transmission function
- **Bluetooth Communication**: BLE interface for remote monitoring and control

## Build Commands

```bash
# Build the project
pio run

# Build and upload to device
pio run --target upload

# Clean build artifacts
pio run --target clean

# Monitor serial output
pio device monitor

# Run static code analysis
pio check
```

## Code Architecture

### Core Components

The system is built around a task scheduler (`TaskScheduler`) with the main loop running at 100ms intervals. Key components:

- **Main Task** (`src/main.cpp:109-122`): Orchestrates all subsystems in the main loop
- **Preferences** (`src/preferences.cpp`): Flash-based persistent storage for distance tracking
- **Speed** (`src/speed.cpp`): Hall sensor interrupt-driven speed calculation with configurable distance per revolution
- **Bluetooth** (`src/bluetooth.cpp`): BLE service providing pitch/roll, winch control, and speed characteristics
- **Incline** (`src/incline.cpp`): Accelerometer-based pitch/roll calculation with low-pass filtering
- **Winch** (`src/winch.cpp`): PWM motor control with enable/disable state management
- **Sound** (`src/sound.cpp`): Audio warnings for steep angles
- **Dig** (`src/dig.cpp`): Rear axle lock servo control

### Key Data Structures

- **PitchRoll** (`include/pitchroll.h`): Stores pitch/roll values with validity flag
- **PreferencesData** (`include/preferences.h:5-8`): Flash storage structure for distance tracking
- **StatusInfo** (`include/statusinfo.h`): System status tracking with change detection

### Hardware Configuration

- **Target**: Arduino Nano 33 BLE (`nano33ble`)
- **Hall Sensor**: Digital pin D4 (interrupt-driven)
- **Toggle Switch**: Digital pin D2 with debouncing
- **Servo**: PWM control for winch motor
- **Sensors**: LSM9DS1 (accelerometer/gyroscope)

### Dependencies

Core libraries managed in `platformio.ini`:
- `Arduino_LSM9DS1`: Sensor interface
- `ArduinoBLE`: Bluetooth Low Energy
- `Servo`: Motor control
- `TaskScheduler`: Task management
- `ezButton`: Switch debouncing
- Custom `NanoBLEFlashPrefs`: Flash storage wrapper

### Configuration

Build flags in `platformio.ini`:
- Task scheduler callbacks enabled
- L298N winch controller support
- Debug mode (commented out by default)

## Development Notes

- Speed calculation uses configurable `mmDistancePerRevolution` (default 49.5mm)
- Distance is persisted to flash every 50 meters to prevent data loss
- Sound warnings triggered at specific pitch (±65°) and roll (±40°/±45°) thresholds
- BLE characteristics update only when values change to optimize battery life
- Main task runs every 100ms coordinating all subsystems