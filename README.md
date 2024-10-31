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
- [License](#license)

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

The following diagram shows the wiring for the gas weight tracker system:

![Gas Cylinder Presentation](https://github.com/user-attachments/assets/6b06d1fe-71e7-4cdb-b42d-5a91803f1e96)


