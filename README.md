# Waspmode: LoRa-Enabled Environmental Monitoring with Ultra-Low Power

**Waspmode** is an ultra-low-power IoT project combining a BME280 sensor with a LoRa module to monitor environmental parameters like temperature, humidity, and pressure. Designed for battery-powered operations, it leverages efficient data transmission and deep sleep modes to minimize energy consumption.

## Features

- **Environmental Sensing**: Reads accurate temperature, humidity, and pressure data using the BME280 sensor.
- **LoRa Communication**: Transmits sensor data over long distances using LoRaWAN at 915 MHz (configurable).
- **Low Power Consumption**: Utilizes the `LowPower` library to enter deep sleep between transmissions, conserving energy.
- **Compact Data Encoding**: Efficiently encodes sensor data for optimized payload size and accuracy.
- **Arduino Compatible**: Built with Arduino IDE, making it easy to modify and extend.

## Applications

- Remote environmental monitoring
- Smart agriculture
- Weather stations
- Battery-powered IoT deployments

## Getting Started

1. **Hardware Requirements**:
   - Arduino-compatible microcontroller
   - BME280 sensor
   - LoRa module (e.g., SX1276/78)
   - Supporting components (wires, resistors, breadboard, etc.)

2. **Setup**:
   - Wire the BME280 and LoRa module to your microcontroller.
   - Update the code with your specific pin configurations.
   - Adjust LoRa frequency based on your region's regulations.

3. **Installation**:
   - Install the required libraries:
     - `LoRa`
     - `Adafruit BME280`
     - `LowPower`
   - Upload the code using the Arduino IDE.
