# **PIC18F4620 Embedded System Project**

This repository contains an embedded systems project developed for the **PIC18F4620** microcontroller. It demonstrates the implementation of various drivers and modules, structured according to the **Microcontroller Abstraction Layer (MCAL)** and **External Control Unit (ECU)** design patterns, ensuring modularity and scalability.

---

## **📁 Project Structure**


---

## **🛠 Getting Started**

### **📦 Prerequisites**

Before you begin, ensure you have the following:

- **MPLAB X IDE** – For project development and debugging  
- **XC8 Compiler** – For compiling code for the PIC18F4620  
- **PIC18F4620 Microcontroller** – Target device  
- **PICkit Programmer (e.g., PICkit 3)** – For uploading the compiled hex file to the microcontroller  

---

## **🔧 Layers Overview**

### **MCAL Layer**
- Contains low-level drivers that directly interface with the **PIC18F4620 hardware peripherals** (e.g., GPIO, Timers, ADC).
- Each driver is modular and reusable across different projects.

### **ECU Layer**
- Built on top of the MCAL layer.
- Includes higher-level modules like **LED**, **button**, and **DC motor control**, encapsulating peripheral interactions.

### **Application Layer**
- Defined in `application.c` and `application.h`.
- Implements the actual logic and flow of the system using MCAL and ECU modules.

---

## **🚀 Deployment**

1. Clone the repository.
2. Open the project in **MPLAB X IDE**.
3. Build the project using the **XC8 compiler**.
4. Use **PICkit 3** or compatible programmer to upload the `.hex` file located in the `dist/` folder to your **PIC18F4620**.

---

## **🧪 Testing & Simulation**

- The `sim/` folder includes simulation files for testing in environments like **MPLAB SIM**.
- The `test/` directory contains **unit tests** to verify the behavior of individual modules and layers.

---

## **📜 License**

This project is licensed under the **MIT License**. See `LICENSE` file for details.

---

## **👨‍💻 Author**

- **Abdelrahman Basyouni** – [GitHub Profile](https://github.com/Albakatoshy)

---

