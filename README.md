# STM32F4xx-Based Digital Multimeter

This project implements a digital multimeter using the **STM32F4xx** series microcontroller (ARM Cortex-M4). It is capable of measuring:

- **DC Voltage**
- **DC Current**
- **AC Voltage**

The design utilizes the internal **12-bit ADC** of the STM32F4xx along with external signal conditioning circuits, including:
- **Voltage dividers** for high-voltage DC measurement,
- **Precision shunt resistors** for DC current sensing,
- **AC coupling + rectification stage** for AC voltage.

Measured values are processed by the microcontroller and displayed via an **LCD** or **UART terminal**.

## Features
- **Multiple measurement ranges** (auto-ranging or manual, depending on firmware version)
- **Input overload protection**
- **Calibration support** for improved accuracy
- **Low-cost, educational-grade** hardware design
- Firmware written in **C** using **STM32Cube HAL libraries**

## Hardware Requirements
- **STM32F407VET6** (or compatible STM32F4xx) development board
- External front-end circuitry (schematics included in `/hardware`)
- Optional: **16x2 LCD**, **OLED display**, or **USB-UART adapter**

## Software Environment
- **STM32CubeIDE** (or Keil uVision / Makefile-based toolchain)
- **STM35CubeF4 HAL drivers**

> ⚠️ **Warning**: This project is intended for learning and prototyping. Always observe proper electrical safety practices when measuring live circuits.

