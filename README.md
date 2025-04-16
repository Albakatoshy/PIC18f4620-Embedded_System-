# PIC18f4620-Embedded_System-
PIC18f4620 Embedded System Project
This repository contains an embedded systems project developed for the PIC18F4620 microcontroller. The project demonstrates the implementation of various drivers and modules, structured according to the Microcontroller Abstraction Layer (MCAL) and the External Control Unit (ECU) design patterns.
GitHub
GitHub

Project Structure
MCAL_layer/: Contains low-level drivers interfacing directly with the PIC18F4620 hardware peripherals.

ECU_layer/: Houses higher-level modules built upon MCAL drivers, such as LEDs, buttons, and DC motors.

application.c / application.h: Main application logic that utilizes the ECU and MCAL layers to perform desired operations.

build/: Build artifacts generated during the compilation process.

dist/: Distribution files, including the final hex file ready for deployment.

sim/: Simulation files for testing the application in a virtual environment.

test/: Test cases and related files to verify the functionality of various modules.

Makefile: Automates the build process using defined rules and dependencies.

Getting Started
Prerequisites
MPLAB X IDE

XC8 Compiler

PIC18F4620 Microcontroller

PICkit Programmer (e.g., PICkit 3)