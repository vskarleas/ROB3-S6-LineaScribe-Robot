#include <Servo.h>

const int buttonPin = 8;
const int ledAutoPin = 10;
const int ledManualPin = 9;
const int servo1Pin = 6;
const int servo2Pin = 5;
const int servo3Pin = 3;
const int joystickButtonPin = 7;
const int verticalJoystickPin = A1;
const int horizontalJoystickPin = A0;

Servo servo1;
Servo servo2;
Servo servo3;

int buttonState = 0;
int previousButtonState = 0;
int clickCount = 0;
int currentState = 0;

int trajectoryPoints[100][2];  // Array to store trajectory points
int trajectoryIndex = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledAutoPin, OUTPUT);
  pinMode(ledManualPin, OUTPUT);
  pinMode(joystickButtonPin, INPUT_PULLUP);

  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
}

void loop() {
  checkButton();
  if (clickCount == 1) {
    // Change state on single press
    currentState = (currentState == 1) ? 2 : 1;
    clickCount = 0;
  } else if (clickCount == 2) {
    // Execute current state on double press
    clickCount = 0;
    if (currentState == 1) {
      runAutomaticProgram();
      blinkLED(ledAutoPin);
    } else if (currentState == 2) {
      if (digitalRead(joystickButtonPin) == LOW) {
        executeTrajectory();
        blinkLED(ledManualPin);
      }
    }
  }
  // Light both LEDs while waiting for a state selection
  digitalWrite(ledAutoPin, HIGH);
  digitalWrite(ledManualPin, HIGH);
}

void checkButton() {
  buttonState = digitalRead(buttonPin);
  if (buttonState != previousButtonState && buttonState == LOW) {
    clickCount++;
  }
  previousButtonState = buttonState;
  // Turn off LEDs after button press is detected
  digitalWrite(ledAutoPin, LOW);
  digitalWrite(ledManualPin, LOW);
}

void runAutomaticProgram() {
  // Your code to move the servos in a predefined way
  // Example:
  for (int i = 0; i < 10; i++) {
    servo1.write(i * 10);
    servo2.write(90 - i * 5);
    servo3.write(180 - i * 15);
    delay(500);
  }
}

void captureTrajectory() {
  trajectoryPoints[trajectoryIndex][0] = analogRead(verticalJoystickPin);
  trajectoryPoints[trajectoryIndex][1] = analogRead(horizontalJoystickPin);
  trajectoryIndex++;
  if (trajectoryIndex >= 100) {
    trajectoryIndex = 0;
  }
}

void executeTrajectory() {
  for (int i = 0; i < 100; i++) {
    // Use trajectoryPoints[i][0] and trajectoryPoints[i][1] to move servos
    // Example:
    servo1.write(trajectoryPoints[i][0]);
    servo2.write(trajectoryPoints[i][1]);
    servo3.write(map(trajectoryPoints[i][1], 0, 1023, 0, 180));
    delay(100);
  }
}

void blinkLED(int ledPin) {
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPin, HIGH);
    delay(100);
  }
}