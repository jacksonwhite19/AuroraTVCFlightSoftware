// Include the pinout definitions (ensure this file is in your project folder)
#include "MatkeH743_Pinout.h"

void setup() {
    // Initialize LED pins as outputs
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
}

void loop() {
    // Turn LED1 on, LED2 off
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, LOW);
    delay(500);

    // Turn LED1 off, LED2 on
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, HIGH);
    delay(500);
}
