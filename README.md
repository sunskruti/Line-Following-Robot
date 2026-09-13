# 🤖 Autonomous Line-Following Robot

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform](https://img.shields.io/badge/Platform-Arduino-00979C.svg?logo=arduino)](https://www.arduino.cc/)
[![Language](https://img.shields.io/badge/Language-C%2B%2B-blue.svg?logo=c%2B%2B)](https://isocpp.org/)
[![Simulation](https://img.shields.io/badge/Simulation-Python%203-3776AB.svg?logo=python)](https://www.python.org/)

An autonomous 2-wheel differential drive robot designed to accurately track a black line on a white surface using a 3-channel infrared (IR) sensor array, an Arduino microcontroller, and an L298N dual H-bridge motor driver.

---

## 🌟 Features

- **3-Sensor Feedback Array**: High-precision edge and center tracking (TCRT5000 / FC-51).
- **Smooth Differential Steering**: Independent PWM speed control for left and right motors.
- **Fail-Safe Logic**: Auto-stop when line is lost or unexpected sensor combinations occur.
- **Comprehensive Hardware Documentation**: Complete pinout and circuit diagrams included.
- **Python Kinematics Simulator**: Built-in 2D simulation to test sensor-to-action control logic before flashing hardware.

---

## 🛠️ Components & Hardware Requirements

| Component | Specification | Quantity |
|---|---|---|
| **Microcontroller** | Arduino UNO / Nano | 1 |
| **Motor Driver** | L298N Dual H-Bridge Driver Module | 1 |
| **Line Sensors** | TCRT5000 / FC-51 Infrared Tracking Modules | 3 |
| **Motors** | DC TT Gear Motors (3V-6V) with Rubber Wheels | 2 |
| **Chassis** | 2WD Acrylic Smart Car Chassis with Caster Wheel | 1 |
| **Power Source** | 2x 18650 Li-ion Batteries (7.4V) or 9V Battery Pack | 1 |
| **Wires & Switch** | Breadboard / Jumper Wires & SPST Switch | Assorted |

---

## 🔌 Pinout & Wiring Connections

### 1. IR Sensor Array
| Sensor | Sensor Pin | Arduino Pin | Logic State (Black Line Detected) |
|---|---|---|---|
| **Left Sensor** | OUT | **D2** | `LOW` |
| **Center Sensor** | OUT | **D3** | `LOW` |
| **Right Sensor** | OUT | **D4** | `LOW` |
| *VCC & GND* | VCC / GND | 5V / GND | — |

### 2. L298N Motor Driver
| Driver Pin | Arduino Pin | Function |
|---|---|---|
| **ENA** (PWM) | **D5** | Left Motor Speed (0–255) |
| **IN1** | **D6** | Left Motor Forward |
| **IN2** | **D7** | Left Motor Reverse |
| **ENB** (PWM) | **D9** | Right Motor Speed (0–255) |
| **IN3** | **D10** | Right Motor Forward |
| **IN4** | **D11** | Right Motor Reverse |

> 📖 *For complete schematic details, see [CIRCUIT_DIAGRAM.md](circuit_diagrams/CIRCUIT_DIAGRAM.md).*

---

## 🧠 Control Logic Truth Table

| Left Sensor | Center Sensor | Right Sensor | Robot Action | Motor Left Speed | Motor Right Speed |
|:---:|:---:|:---:|:---:|:---:|:---:|
| `1` (Off) | `0` (On) | `1` (Off) | **Move Forward** | 150 | 150 |
| `0` (On) | `X` | `1` (Off) | **Turn Left** | 100 (Reverse/Slow) | 150 (Forward) |
| `1` (Off) | `X` | `0` (On) | **Turn Right** | 150 (Forward) | 100 (Reverse/Slow) |
| `0` (On) | `0` (On) | `0` (On) | **Intersection / Forward** | 150 | 150 |
| `1` (Off) | `1` (Off) | `1` (Off) | **Stop (Line Lost)** | 0 | 0 |

---

## 📁 Repository Structure

```
Line-Following-Robot/
├── .gitignore                      # Git ignore rules
├── LICENSE                         # MIT License
├── README.md                       # Project documentation
├── arduinocode.ino                 # Main Arduino source file (root)
├── code/
│   └── line_follower.ino          # Modular Arduino source file
├── circuit_diagrams/
│   └── CIRCUIT_DIAGRAM.md         # Detailed wiring and connection schematics
└── simulation/
    └── line_follower_sim.py       # 2D differential drive kinematics simulation
```

---

## 🚀 Getting Started

### 1. Arduino Upload
1. Connect your Arduino Uno / Nano to your computer via USB.
2. Open [arduinocode.ino](arduinocode.ino) in the [Arduino IDE](https://www.arduino.cc/en/software).
3. Select your board (`Tools > Board > Arduino Uno`) and serial port (`Tools > Port`).
4. Click **Upload** (Ctrl + U / Cmd + U).

### 2. Running Python Simulation
To verify the sensor control algorithm before hardware testing:
```bash
python simulation/line_follower_sim.py
```

### 3. Sensor Calibration & Tuning
- Place the robot over the white background and turn the potentiometer on each sensor module until the LED just turns OFF.
- Place the sensor over the black line; the indicator LED should turn ON.
- Adjust `FORWARD_SPEED`, `TURN_SPEED_FAST`, and `TURN_SPEED_SLOW` in the code depending on battery charge and track tightness.

---

## 📄 License

Distributed under the MIT License. See [LICENSE](LICENSE) for more information.
