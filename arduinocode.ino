
const int leftSensor = 2;
const int centerSensor = 3;
const int rightSensor = 4;


const int ENA = 5;  
const int IN1 = 6;
const int IN2 = 7;

const int ENB = 9; 
const int IN3 = 10;
const int IN4 = 11;

void setup() {
  pinMode(leftSensor, INPUT);
  pinMode(centerSensor, INPUT);
  pinMode(rightSensor, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int left = digitalRead(leftSensor);
  int center = digitalRead(centerSensor);
  int right = digitalRead(rightSensor);

 
  if (center == LOW && left == HIGH && right == HIGH) {
    moveForward();
  }
  else if (left == LOW) {
    turnLeft();
  }
  else if (right == LOW) {
    turnRight();
  }
  else if (left == LOW && right == LOW && center == LOW) {
    moveForward();  
  else {
    stopMotors();  

  delay(10);
}


void moveForward() {
  analogWrite(ENA, 150);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  analogWrite(ENB, 150);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft() {
  analogWrite(ENA, 100);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  analogWrite(ENB, 150);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  analogWrite(ENA, 150);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  analogWrite(ENB, 100);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
