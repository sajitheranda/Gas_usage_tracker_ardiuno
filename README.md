# Gas Weight Tracker System

An **Arduino-based Gas Weight Tracker System** designed to continuously measure and monitor the weight of a gas cylinder in real time. This system notifies users of weight changes that may indicate a gas leak, with data securely stored in Firebase Realtime Database for remote access.

---

## Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Circuit Diagram](#circuit-diagram)
- [Installation](#installation)
- [Configuration](#configuration)
- [Usage](#usage)
- [Troubleshooting](#troubleshooting)

---

## Project Overview

This project monitors the weight of a gas cylinder every minute using a load cell connected to an ESP8266 microcontroller. The ESP8266 transmits the weight data to a **Firebase Realtime Database** over Wi-Fi. If the gas weight drops rapidly, the system triggers an alarm to notify the user of a potential leak. 

## Features


- **Real-time Weight Measurement**:  
   Continuously monitors the weight of a gas cylinder using a load cell sensor, allowing for accurate and up-to-date tracking of gas usage.

- **Periodic Data Logging to Firebase**:  
   The system measures gas weight every minute and automatically sends this data to Firebase Realtime Database. This allows users to remotely monitor gas levels and view historical usage data from anywhere with internet access.

- **Leak Detection and Alarm System**:  
   In addition to tracking weight, the system detects sudden drops in weight that may indicate a gas leak. When a weight drop beyond a set threshold is detected, the system triggers an alarm to alert the user, helping to prevent hazardous situations.

- **Remote Alarm Control**:  
   The alarm status is updated in Firebase, so it can be remotely controlled or monitored by users via the Firebase Realtime Database. This feature enables users to stay informed about potential leaks even when they are not near the system.

- **Automatic Time Synchronization**:  
   Using NTP (Network Time Protocol), the system synchronizes with an external time server to ensure all recorded weight data has accurate timestamps. This feature ensures reliable, time-stamped data logging, which is crucial for analyzing gas usage trends over time.

- **Low Power Consumption**:  
   Designed with efficient power usage in mind, the system only updates the database once per minute, conserving energy. This feature is especially beneficial for long-term deployment or for setups where power consumption needs to be minimized.

- **Flexible and Customizable**:  
   Built using open-source tools and libraries, the project can be easily customized or expanded for additional features, such as integrating with different IoT platforms, adding more sensors, or altering alarm parameters.

## Hardware Requirements

- **NodeMCU (ESP8266)**: Microcontroller used to manage data processing, Wi-Fi connectivity, and Firebase integration.
- **HX711 Load Cell Amplifier**: Amplifier module for accurately reading the weight data from the load cell.
- **20kg Load Cell**: Load sensor capable of measuring up to 20kg, used to monitor the gas cylinder's weight.
- **Buzzer**: Used for audible alerts in case of sudden weight drops, indicating a potential gas leak.
- **Connecting Wires**: For connecting the load cell, HX711 amplifier, and buzzer to the NodeMCU.

## Software Requirements

- **Arduino IDE** with ESP8266 support
- Required libraries:
  - `ESP8266WiFi`
  - `FirebaseESP8266`
  - `ArduinoJson`
  - `NTPClient`
  - `HX711`

## Circuit Diagram

<div align="center">
  <img src="https://github.com/user-attachments/assets/6b06d1fe-71e7-4cdb-b42d-5a91803f1e96" alt="Gas Cylinder Presentation" height="400">
  <p><em>Figure 1: Circuit diagram </em></p>
</div>

- **Load Cell**: This sensor measures the weight of the gas cylinder. It is connected to the HX711 amplifier, which converts the small analog signal from the load cell into a digital signal that the NodeMCU can read.

- **HX711 Amplifier**: This module amplifies the load cell’s signal and connects to the NodeMCU as follows:
  - `DT` (Data) pin on HX711 -> `D6` pin on NodeMCU
  - `SCK` (Clock) pin on HX711 -> `D7` pin on NodeMCU
  - `VCC` -> `3V` on NodeMCU
  - `GND` -> `GND` on NodeMCU

- **Buzzer**: The buzzer is connected to the NodeMCU to sound an alarm in case of a sudden weight drop, indicating a possible gas leak.
  - Connect the positive terminal of the buzzer to `D0` on NodeMCU.
  - Connect the ground terminal to `GND` on NodeMCU.

## Installation

1. **Clone the Repository**:  
   Clone the repository to your local machine using the following command:
   ```bash
   git clone https://github.com/sajitheranda/Gas_usage_tracker_ardiuno.git

2. **Set up Arduino IDE**:
   - Install [Arduino IDE](https://www.arduino.cc/en/software).
   - Add ESP8266 support by going to `File` > `Preferences`, and adding `http://arduino.esp8266.com/stable/package_esp8266com_index.json` to the Additional Board Manager URLs.

3. **Install Libraries**:
   - Go to `Sketch` > `Include Library` > `Manage Libraries`.
   - Install the following libraries:
     - `ESP8266WiFi`
     - `FirebaseESP8266`
     - `ArduinoJson`
     - `NTPClient`
     - `HX711`

4. **Upload Code**:
   - Open the `gas_weight_tracker.ino` file.
   - Update Wi-Fi and Firebase credentials in the code.
   - Connect your ESP8266, select the correct board and port, and upload the code.

## Configuration

In the source code, update the following sections:

- **Wi-Fi credentials**:
  ```cpp
  const char* ssid = "your_SSID";
  const char* pass = "your_PASSWORD";

- **Firebase credentials**:
  ```cpp
  const char* firebaseHost = "your_firebase_database_url";
  const char* firebaseAuth = "your_firebase_database_secret";


## Usage

1. **Power on the Device**:  
   Power on the device to connect to Wi-Fi and initialize the load cell sensor.

2. **Monitoring**:  
   Every minute, the system will check the weight and push data to Firebase. The system also continuously checks for any significant weight drop.

3. **Alarm**:  
   If a weight drop is detected, indicating a possible gas leak, the system activates the alarm.

## Troubleshooting

- **Wi-Fi Not Connecting**:  
   - Ensure SSID and password are correctly entered.
   - Check if the ESP8266 is within Wi-Fi range.

- **Firebase Connection Issues**:  
   - Confirm Firebase URL and authentication token are correctly set.
   - Verify the Firebase Realtime Database rules permit read and write access.
