# Arduino-HAB

**High Altitude Balloon (HAB) Flight Code**  
Developed by the CUonOrbit Team

This Arduino codebase is designed to run on an **Arduino Uno R4** and supports sensor data logging and telemetry for CUonOrbit's High Altitude Balloon launches.

---

## 🚀 Project Overview

The Arduino-HAB system is responsible for collecting environmental and positional data during the HAB's flight. The key components include:

- **BMP180** for temperature and pressure readings
- **GPS Module** for location tracking
- **MicroSD Card Module** for onboard data logging

All sensor readings are timestamped and written to a log file for post-flight analysis.

---

## 📦 Hardware Requirements

| Component          | Power Source | Notes                       |
|--------------------|--------------|-----------------------------|
| Arduino Uno R4     | USB / Battery| Main controller             |
| BMP180 Sensor      | 5V           | I2C connection              |
| GPS Module         | 3.3V         | UART connection             |
| MicroSD Card Module| 5V           | SPI connection              |

**📍 Pin connections are defined in [`config.h`](config.h).**

## 🛠️ Getting Started

1. **Install the required Arduino libraries:**
   - Adafruit BMP085/BMP180 Unified
   - TinyGPS++
   - SD

2. **Connect your modules to the Arduino Uno R4** according to the pin definitions in `config.h`.

3. **Compile and upload** the `Arduino-HAB.ino` file to the board using the Arduino IDE or Arduino CLI.

4. **Insert a properly formatted micro SD card** into the module before powering the board to enable data logging.