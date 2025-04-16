#include "MatekH743_Pinout.h"
// Servos connected on PA0 and PA1 >> Motor3 and Motor4
// xServo == Motor 3
// yServo == Motor 4
#include <Servo.h>
#include <math.h>

Servo servoX;
Servo servoY;

const int centerPos = 90;
const int sweepRange = 16;
const int stepDelay = 35;  // ms between servo steps

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
      servoY.write(centerPos);
      Serial.print("Sweeping X → ");
      Serial.println(currentPos);
    } else {
      servoY.write(currentPos);
      servoX.write(centerPos);
      Serial.print("Sweeping Y → ");
      Serial.println(currentPos);
    }

    posOffset += direction;

    if (abs(posOffset) > sweepRange) {
      direction *= -1;
      posOffset += direction;  // Prevent stuttering at endpoints

      if (direction > 0) {
        if (!sweepingX) {
          // Finished Y sweep → now do circular
          Serial.println("Starting circular sweep");
          delay(200);
          doCircularSweep();
        }

        sweepingX = !sweepingX;  // Switch servo phase
        Serial.println(sweepingX ? "Switching to X axis" : "Switching to Y axis");
        delay(300);  // Optional pause
      }
    }
  }
}

void doCircularSweep() {
  for (int angleDeg = 0; angleDeg <= 360; angleDeg += 5) {
    float radians = angleDeg * DEG_TO_RAD;
    int xPos = centerPos + sweepRange * cos(radians);
    int yPos = centerPos + sweepRange * sin(radians);

    servoX.write(xPos);
    servoY.write(yPos);

    Serial.print("Circular X: ");
    Serial.print(xPos);
    Serial.print(" | Y: ");
    Serial.println(yPos);

    delay(20);  // Control speed of the circle
  }

  // Return to center after circle
  servoX.write(centerPos);
  servoY.write(centerPos);
  delay(300);
}
