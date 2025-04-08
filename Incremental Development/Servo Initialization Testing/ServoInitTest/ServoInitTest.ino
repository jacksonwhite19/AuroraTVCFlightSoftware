#include "MatekH743_Pinout.h"
// Servos connected on PA0 and PA1 >> Motor3 and Motor4
// xServo == Motor 3
// yServo == Motor 4
#include <Servo.h>

Servo servoX;
Servo servoY;

const int centerPos = 90;
const int sweepRange = 12;
const int stepDelay = 70;  // ms between servo steps

int posOffset = 0;
int direction = 1;
bool sweepingX = true;  // Start with X servo

unsigned long lastMoveTime = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Servos initializing in 4 sec...");
  delay(4000);

  servoX.attach(PA0);  // X-axis
  servoY.attach(PA1);  // Y-axis

  // Center both servos
  servoX.write(centerPos);
  servoY.write(centerPos);

  delay(500);  // Let servos settle before starting sweep
  Serial.println("X and Y servos centered at 90 degrees");
}

void loop() {
  unsigned long now = millis();
  if (now - lastMoveTime >= stepDelay) {
    lastMoveTime = now;

    int currentPos = centerPos + posOffset;

    if (sweepingX) {
      servoX.write(currentPos);
      servoY.write(centerPos);  // Keep Y centered
      Serial.print("Sweeping X → ");
      Serial.println(currentPos);
    } else {
      servoY.write(currentPos);
      servoX.write(centerPos);  // Keep X centered
      Serial.print("Sweeping Y → ");
      Serial.println(currentPos);
    }

    posOffset += direction;

    if (abs(posOffset) > sweepRange) {
      direction *= -1;
      posOffset += direction;  // Prevent stuttering at endpoints

      if (direction > 0) {
        sweepingX = !sweepingX;  // Switch servo after each full cycle
        Serial.println(sweepingX ? "Switching to X axis" : "Switching to Y axis");
        delay(500);  // Optional pause between switching
      }
    }
  }
}
