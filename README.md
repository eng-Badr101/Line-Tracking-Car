# 🛠️ Line Tracking Car using Arduino

This project is a simple **Line Following Robot Car** built with an Arduino Uno, 5 IR sensors, and a motor driver module. The car follows a black line on a white surface by analyzing IR sensor data and adjusting its motor speed and direction accordingly.

## 🚗 Description

The line tracking car uses a total of **5 infrared sensor pairs** (5 transmitters and 5 receivers) to detect the path (black line) beneath it. Each sensor pair is positioned from far left to far right:

* **S1 (A1)** – Far Left
* **S2 (A2)** – Left
* **S3 (A3)** – Center
* **S4 (A4)** – Right
* **S5 (A5)** – Far Right

Based on the input values from these sensors, the Arduino processes the logic to move the car **forward**, take **slight turns**, make **sharp turns**, or **stop** when no line is detected.

## 🧰 Components Used

* Arduino Uno
* 5x Infrared Sensors (IR transmitter and receiver pairs)
* L298N Motor Driver
* 2x DC Motors
* Chassis with wheels
* Power supply (battery pack or USB)
* Jumper wires and breadboard (if needed)

## 🔌 Wiring Summary

| Component    | Arduino Pin |
| ------------ | ----------- |
| Motor IN1    | 7           |
| Motor IN2    | 8           |
| Motor IN3    | 9           |
| Motor IN4    | 10          |
| Motor ENA    | 6 (PWM)     |
| Motor ENB    | 11 (PWM)    |
| IR Sensor S1 | A1          |
| IR Sensor S2 | A2          |
| IR Sensor S3 | A3          |
| IR Sensor S4 | A4          |
| IR Sensor S5 | A5          |

## 🧠 Logic Overview

The car uses the sensor readings to make decisions like:

* Move forward when the center is aligned and both sides detect the line.
* Slightly turn when one side deviates.
* Make a sharp turn if the line is at one extreme.
* Stop if the line is lost or completely detected under all sensors (e.g., at a junction or end).

## 🧾 Arduino Code

```cpp
// Motor Pins
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 10
#define ENA 6
#define ENB 11

// Sensor Pins
#define S1 A1  // Far Left
#define S2 A2  // Left
#define S3 A3  // Center
#define S4 A4  // Right
#define S5 A5  // Far Right

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);

  Serial.begin(9600);
}

void loop() {
  int s1 = digitalRead(S1);
  int s2 = digitalRead(S2);
  int s3 = digitalRead(S3);
  int s4 = digitalRead(S4);
  int s5 = digitalRead(S5);

  Serial.print(s1); Serial.print(" ");
  Serial.print(s2); Serial.print(" ");
  Serial.print(s3); Serial.print(" ");
  Serial.print(s4); Serial.print(" ");
  Serial.println(s5);

  if (s2 == 1 && s3 == 0 && s4 == 1) {
    forward();
  } 
  else if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0 && s5 == 0) {
    stopMotors();
  }
  else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 1) {
    stopMotors();
  }
  else if (s3 == 1 && s2 == 0 && s4 == 1) {
    slightLeft();
  }
  else if (s3 == 1 && s2 == 1 && s4 == 0) {
    slightRight();
  }
  else if (s1 == 0 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 1) {
    turnLeft();
  }
  else if (s5 == 0 && s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1) {
    turnRight();
  }
  else {
    stopMotors();
  }

  delay(500);
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
}

void slightLeft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 75);
  analogWrite(ENB, 100);
}

void slightRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 100);
  analogWrite(ENB, 75);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 100);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 100);
  analogWrite(ENB, 0);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
```

## 🧪 How to Use

1. Upload the code to your Arduino Uno.
2. Power the circuit using a suitable power source.
3. Place the car on a track with a clear black line.
4. Watch your bot follow the path intelligently!

