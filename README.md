# Bare-Metal Avionics IMU Auto-Detect HAL

## Overview
This repository contains a custom, bare-metal C++ Hardware Abstraction Layer (HAL) built for flight computer avionics. It is designed to interface directly with I2C Inertial Measurement Units (IMUs), specifically the **MPU6050** and the **SparkFun ICM-20948**, using an Arduino MKR (32-bit ARM Cortex-M0+).

Instead of relying on bloated commercial libraries, this driver executes direct register-level I2C commands to extract raw accelerometer data and scale it into usable G-forces for flight dynamics calculations.

## Core Features
* **Polymorphic Architecture:** Uses an Object-Oriented Interface (`GenericIMU.h`) allowing the main flight computer to remain completely hardware-agnostic.
* **Smart Auto-Detection:** The initialization sequence automatically pings the I2C bus for `WHO_AM_I` factory ID registers (`0x68` for MPU, `0xEA` for ICM) and dynamically loads the correct software translator at boot.
* **Strict 3.3V Logic:** Fully integrated for the Arduino MKR architecture, operating natively at 3.3V without the need for external logic-level shifting.
* **Bare-Metal Efficiency:** Stripped of unnecessary interrupt configurations and DMP bloat, focusing purely on high-speed, sequential 6-byte I2C data retrieval and G-force scaling.

## Repository Structure
* `/src`: Contains the abstract base class and the specific `.h` and `.cpp` driver files containing the hex register maps for the sensors.
* `/examples`: Contains the main Arduino sketch demonstrating the bus scanning, `WHO_AM_I` interrogation, and continuous polymorphic data reading.
* `/references`: Contains the original, uncondensed commercial library code and datasheets referenced during the reverse-engineering phase of this driver.

## Hardware Wiring (Arduino MKR)
| IMU Pin (SparkFun ICM / Generic MPU) | Arduino MKR Pin | Function |
| :--- | :--- | :--- |
| **VCC / VIN** | **VCC** | 3.3V Power |
| **GND** | **GND** | Ground |
| **SDA** | **Pin 11** | I2C Data |
| **SCL** | **Pin 12** | I2C Clock |

## Usage
1. Wire the sensor to the MKR board via the I2C pins.
2. Flash the `IMU_AutoDetect.ino` sketch.
3. Open the Serial Monitor at 9600 baud. 
4. The system will auto-identify the connected silicon and begin streaming clean, scaled X, Y, and Z acceleration data in Gs.
