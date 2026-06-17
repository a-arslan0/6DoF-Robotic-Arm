# 6-DOF 3D Printed Robotic Arm

Welcome to the repository for my 6 Degrees of Freedom (6-DOF) robotic arm project. This project features a fully 3D-printable mechanical structure designed in SolidWorks and a custom motion control sequence powered by Arduino. 

It is designed to be an accessible, educational, and highly modifiable platform for robotics enthusiasts and engineering students.

## ⚙️ Features
* **6 Degrees of Freedom:** Full spatial manipulation including Base, Shoulder, Elbow 1, Elbow 2, Wrist, and Gripper.
* **Smooth Motion Control:** Custom Arduino functions utilizing microsecond-level PWM adjustments for fluid, jitter-free movements.
* **Open Source CAD:** Includes both `.STL` files for immediate 3D printing and `.STEP` (AP214) files for easy modification, color preservation, and assembly visualization.

## 🛠️ Hardware Requirements (Bill of Materials)
To build this robotic arm, you will need the following electronic components:
* **3x MG995 Servos:** High-torque metal gear servos used for the heavy-lifting lower joints (Base, Shoulder, and primary Elbow).
* **3x MG90S Micro Servos:** Lightweight metal gear servos used for the precise upper joints (secondary Elbow, Wrist, and Gripper).
* **1x PCA9685 PWM Servo Driver:** 16-channel, 12-bit I2C interface board used to efficiently control all 6 servos without overloading the Arduino's internal timers.
* **1x Arduino Microcontroller:** (Uno, Nano, or Mega will work perfectly).
* **External Power Supply:** A dedicated 5V/6V high-current power supply for the PCA9685 board (Do not power 6 servos directly from the Arduino 5V pin).

## 💻 Software & Libraries
The control software is written in C++ for the Arduino environment. You will need to install the following library via the Arduino Library Manager before uploading the code:
* [Adafruit PWM Servo Driver Library](https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library)

## 🚀 Installation & Usage
1. **3D Printing:** Print all the parts located in the `3D_Models` folder. Standard PLA or PETG works great. 
2. **Assembly:** Assemble the robotic arm using the provided STEP file as a visual guide.
3. **Wiring:** * Connect the Arduino to the PCA9685 via I2C (`SDA` and `SCL` pins).
   * Connect your external power supply to the PCA9685 terminal block.
   * Plug the servos into the PCA9685 corresponding to the pin definitions in the code (Base = Pin 0, Shoulder = Pin 1, etc.).
4. **Upload Code:** Open the `.ino` file in the `Software` folder, verify your board and port, and upload it to your Arduino.

## 📝 License
This project is open-source and available under the [MIT License](LICENSE). Feel free to use, modify, and distribute this project as you see fit!
