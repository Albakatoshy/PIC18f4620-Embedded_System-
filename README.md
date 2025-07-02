# PIC18F4620 Embedded System Drivers & Applications

This repository contains a comprehensive set of drivers and embedded applications built for the **PIC18F4620** microcontroller. It includes full implementations of **MCAL (Microcontroller Abstraction Layer)** drivers, along with various **ECU (Electronic Control Unit)** drivers for external modules like LCDs, motors, sensors, and I2C devices. The goal is to provide a modular and reusable driver library for embedded systems projects.

---

## 🔧 Layers & Architecture

This project follows a layered architecture:

- **MCAL (Microcontroller Abstraction Layer):**  
  Fully implemented low-level drivers for all key PIC18F4620 peripherals:
  - DIO (Digital Input/Output)
  - Timers
  - External Interrupts
  - ADC
  - I2C (Master Mode)
  - USART
  - EEPROM
  - CCP (PWM and Capture)
  - Watchdog Timer
  - Oscillator Configuration

- **ECUAL (ECU Abstraction Layer):**  
  High-level drivers built on top of MCAL to interface with real-world modules.

---

## 📦 Included ECU Drivers

The repository includes complete drivers for several widely used peripheral modules:

### ✅ LCD (16x2 Character LCD)
- 4-bit mode operation
- Functions to write characters, strings, and custom symbols

### ✅ DC Motor Driver
- H-Bridge control via GPIO or PWM
- Functions for clockwise, counter-clockwise, and stop

### ✅ RTC – DS1307 (Real-Time Clock)
- I2C-based real-time clock driver
- Read/write time and date
- BCD-to-decimal conversion included

### ✅ EEPROM – 1K Serial (5V I2C)
- Support for 24C01C and compatible I2C EEPROMs
- Byte-level read/write operations with address handling

### ✅ Temperature Sensor – TC74
- I2C digital temperature sensor
- Read current temperature in °C

### ✅ Additional Drivers
- 7-Segment Display (via BCD or GPIO)
- Push Button with debounce logic
- Keypad scanning (4x4)
- Buzzer control
- LED control

---

## 🛠️ Tools Used

- **Microcontroller:** PIC18F4620  
- **IDE:** MPLAB X IDE  
- **Compiler:** MPLAB XC8  
- **Simulation:** Proteus ISIS  
- **Language:** C

---

## 🚀 How to Run

1. Open the desired project in **MPLAB X IDE**.
2. Compile using the **XC8 compiler**.
3. Flash the hex file to the **PIC18F4620** using a programmer (e.g. PICkit 3/4).
4. For simulation, open the associated `.dsn` file in **Proteus**.

---

## 🎯 Purpose

This repository is intended to:
- Help learners understand layered driver architecture
- Provide reusable and tested drivers for common ECUs
- Support quick prototyping and embedded project development

---

## ✅ Conclusion

This project demonstrates a complete embedded systems development approach using the PIC18F4620. With fully implemented MCAL drivers and a wide range of tested ECU drivers, the repository serves as a robust foundation for both academic and practical embedded applications. Whether you’re a student, engineer, or hobbyist, you’ll find reusable components and real-world examples to accelerate your development.

---

## 📬 Contact

**Author:** Abdelrahman Basyouni  
**Email:** es-abdelrahman.Basyouni2027@alexu.edu.eg  
**GitHub:** [Albakatoshy](https://github.com/Albakatoshy)

---
