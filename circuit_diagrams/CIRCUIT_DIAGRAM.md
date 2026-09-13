# Circuit Diagram & Wiring Reference

This document outlines the wiring and hardware connections for the 3-sensor Line Following Robot using an **Arduino Uno / Nano**, **L298N Motor Driver**, and **3x Infrared (IR) Proximity Sensors** (e.g., TCRT5000 or FC-51 modules).

---

## 🔌 Hardware Pinout Table

### 1. IR Sensor Array to Arduino

| Sensor Module | Sensor Pin | Arduino Pin | Description |
|---|---|---|---|
| **Left IR Sensor** | VCC | 5V | Power supply (+5V) |
| | GND | GND | Common Ground |
| | OUT / DO | **D2** | Digital Output (LOW = Line Detected) |
| **Center IR Sensor** | VCC | 5V | Power supply (+5V) |
| | GND | GND | Common Ground |
| | OUT / DO | **D3** | Digital Output (LOW = Line Detected) |
| **Right IR Sensor** | VCC | 5V | Power supply (+5V) |
| | GND | GND | Common Ground |
| | OUT / DO | **D4** | Digital Output (LOW = Line Detected) |

---

### 2. L298N Motor Driver to Arduino & Motors

| L298N Pin | Arduino Pin / Component | Function |
|---|---|---|
| **ENA** (Remove jumper) | **D5** (PWM) | Left Motor Speed Control |
| **IN1** | **D6** | Left Motor Direction (Forward) |
| **IN2** | **D7** | Left Motor Direction (Reverse) |
| **IN3** | **D10** | Right Motor Direction (Forward) |
| **IN4** | **D11** | Right Motor Direction (Reverse) |
| **ENB** (Remove jumper) | **D9** (PWM) | Right Motor Speed Control |
| **OUT1 & OUT2** | Left DC Gear Motor | Left Wheel Drive |
| **OUT3 & OUT4** | Right DC Gear Motor | Right Wheel Drive |

---

### 3. Power Supply Connections

| Power Source | Connection Point | Notes |
|---|---|---|
| **Battery (+)** (7.4V - 12V) | L298N **12V / VMS terminal** | Main motor power |
| **Battery (-)** | L298N **GND terminal** | Common ground |
| **L298N GND** | Arduino **GND** | **CRITICAL:** Common ground reference |
| **L298N 5V Out** (if 5V regulator enabled) | Arduino **VIN / 5V pin** | Supplies power to Arduino & sensors |

> ⚠️ **Important:** Always ensure all GND pins (Battery, L298N, and Arduino) are tied together to share a common reference voltage.

---

## 📐 Schematic Diagram (ASCII)

```
        +-------------------------------------------------+
        |                    BATTERY                      |
        |              (7.4V - 12V Li-ion/Lipo)           |
        +--------------------+----------------------------+
                             | (+)                 | (-)
                             |                     |
                             v                     v
                 +-----------------------+         |
                 |      L298N DRIVER     |         |
                 |  +12V      GND        | <-------+
                 +----+--------+---------+         |
                      | 5V Out |                   |
                      |        | (Common GND)      |
                      v        v                   v
                 +---------------------------------+
                 |          ARDUINO UNO            |
                 | 5V                     GND      |
                 +----+--------------------+-------+
                      |                    |
       +--------------+                    +--------------+
       | (5V)                                      (GND)  |
       v                                                  v
+--------------+    +----------------+    +---------------+
| LEFT SENSOR  |    | CENTER SENSOR  |    | RIGHT SENSOR  |
| OUT -> Pin 2 |    |  OUT -> Pin 3  |    |  OUT -> Pin 4 |
+--------------+    +----------------+    +---------------+
```

---

## ⚙️ Sensor Calibration

1. Place the robot over the white surface; adjust the onboard potentiometer on each IR module until the sensor LED turns **OFF**.
2. Place the robot over the black line; the sensor LED should turn **ON** (active detection).
3. Ensure the sensors are mounted approximately **5mm to 10mm** above the surface for optimal sensitivity.
