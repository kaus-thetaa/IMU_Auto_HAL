# IMU Auto-Detecting Hardware Abstraction Layer (HAL)
A bare-metal, object-oriented C++ Hardware Abstraction Layer (HAL) for auto-detecting and reading I2C IMUs (MPU6050 &amp; ICM) on Arduino.

## Overview
This repository contains a 100% self-written, bare-metal C++ driver for I2C Inertial Measurement Units (IMUs). Instead of relying on bloated commercial libraries, this project interacts directly with the sensor hardware registers using the standard Arduino `Wire.h` library. 

It implements a robust Object-Oriented Programming (OOP) architecture to create a Hardware Abstraction Layer (HAL). This allows the main microcontroller to seamlessly interface with different physical sensors (like the MPU6050 or ICM series) without changing the main application logic.

## Key Features
* **Bare-Metal I2C Communication:** Direct register reading and bitwise operations to extract raw 16-bit X, Y, and Z accelerometer data.
* **Smart Auto-Detection:** The system pings the `WHO_AM_I` register on the I2C bus at startup to automatically identify the connected hardware and boot the correct driver.
* **Polymorphism & Inheritance:** Utilizes a pure virtual base class (`GenericIMU`) so the main application code remains hardware-agnostic.
* **Lightweight:** Stripped of unnecessary configuration bloat found in standard libraries, optimizing memory and execution speed.

## Repository Structure
* `GenericIMU.h`: The abstract base class (Interface) defining the standard `begin()` and `read()` functions.
* `MPU6050.h` / `MPU6050.cpp`: The specific register maps (e.g., `0x6B` for power management, `0x3B` for data out) and bitwise assembly logic for the MPU6050.
* `ICM.h` / `ICM.cpp`: The specific register maps and logic for the ICM sensor series.
* `AutoDetect_Example.ino`: The main Arduino sketch demonstrating the I2C bus scanning and polymorphic data reading.

## Hardware Wiring (Arduino Uno/Nano)
| IMU Pin | Arduino Pin |
| :--- | :--- |
| VCC | 3.3V or 5V (Board dependent) |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

## Usage
Simply flash the `AutoDetect_Example.ino` to your Arduino, open the Serial Monitor at 9600 baud, and the microcontroller will automatically detect the plugged-in sensor and begin streaming X, Y, and Z axis data.
