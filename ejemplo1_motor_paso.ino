#include <Stepper.h>

// Define the number of steps per revolution for your motor
const int stepsPerRevolution = 1024;  // Adjust according to your motor

// Se inicializa el motor de paso ingresando los pines de las señales en orden: IN4, IN2, IN3, IN1
Stepper myStepper
(stepsPerRevolution, 23, 13, 5, 12);

void setup() {
  // Set the speed of the motor (in RPM)
  myStepper.setSpeed(10);
  // Initialize serial communication
  Serial.begin(115200);
}

void loop() {
  // Move the motor one revolution in one direction
  Serial.println("Moving one revolution clockwise");
  myStepper.step(stepsPerRevolution);
  delay(1000);

  // Move the motor one revolution in the other direction
  Serial.println("Moving one revolution counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(1000);
}
