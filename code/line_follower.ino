// ============================================================================
// Line Following Robot (3 IR Sensor Array with L298N Motor Driver)
// ============================================================================
// Hardware Connections:
// ----------------------------------------------------------------------------
// IR Sensors (Active LOW / detects black line = LOW, white surface = HIGH):
//   - Left Sensor   -> Arduino Pin 2
//   - Center Sensor -> Arduino Pin 3
//   - Right Sensor  -> Arduino Pin 4
//
// L298N Motor Driver:
//   - Left Motor Enable (ENA)   -> Arduino Pin 5  (PWM)
//   - Left Motor Input 1 (IN1)  -> Arduino Pin 6
//   - Left Motor Input 2 (IN2)  -> Arduino Pin 7
//   - Right Motor Enable (ENB)  -> Arduino Pin 9  (PWM)
//   - Right Motor Input 3 (IN3) -> Arduino Pin 10
//   - Right Motor Input 4 (IN4) -> Arduino Pin 11
// ============================================================================

// --- Sensor Pin Definitions ---
const int leftSensor   = 2;
const int centerSensor = 3;
const int rightSensor  = 4;

// --- Motor Driver Pin Definitions (L298N) ---
const int ENA = 5;   // Left Motor Speed Control (PWM)
const int IN1 = 6;   // Left Motor Direction 1
const int IN2 = 7;   // Left Motor Direction 2

const int ENB = 9;   // Right Motor Speed Control (PWM)
const int IN3 = 10;  // Right Motor Direction 1
const int IN4 = 11;  // Right Motor Direction 2

// --- Speed Constants (0 - 255) ---
const int FORWARD_SPEED = 150;
const int TURN_SPEED_FAST = 150;
const int TURN_SPEED_SLOW = 100;

void setup() {
  // Initialize Sensor Pins
  pinMode(leftSensor, INPUT);
  pinMode(centerSensor, INPUT);
  pinMode(rightSensor, INPUT);

  // Initialize Motor Driver Control Pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
  Serial.println(F("Line Following Robot Initialized"));
}

void loop() {
  // Read Digital Values from IR Sensors
  int left   = digitalRead(leftSensor);
  int center = digitalRead(centerSensor);
  int right  = digitalRead(rightSensor);

  // Decision Logic for Line Following (Active LOW: LOW = On Line, HIGH = Off Line)
  if (center == LOW && left == HIGH && right == HIGH) {
    // Center sensor is on the line -> Move straight
    moveForward();
  }
  else if (left == LOW && right == HIGH) {
    // Left sensor detected line -> Turn left to re-align
    turnLeft();
  }
  else if (right == LOW && left == HIGH) {
    // Right sensor detected line -> Turn right to re-align
    turnRight();
  }
  else if (left == LOW && center == LOW && right == LOW) {
    // All sensors on the line (e.g. Cross-intersection / T-junction) -> Move forward
    moveForward();
  }
  else {
    // All sensors off the line or unknown state -> Stop motors safely
    stopMotors();
  }

  delay(10); // Small loop stabilization delay
}

// ============================================================================
// Motor Movement Functions
// ============================================================================

void moveForward() {
  analogWrite(ENA, FORWARD_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  analogWrite(ENB, FORWARD_SPEED);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft() {
  analogWrite(ENA, TURN_SPEED_SLOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  analogWrite(ENB, TURN_SPEED_FAST);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  analogWrite(ENA, FORWARD_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  analogWrite(ENB, TURN_SPEED_SLOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
