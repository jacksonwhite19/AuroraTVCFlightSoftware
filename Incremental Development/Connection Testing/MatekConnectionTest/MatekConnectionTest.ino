#include "MatkeH743_Pinout.h"
// No need to include USBSerial.h or create SerialUSB object - it's already defined

void setup() {
    // Initialize pins
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    
    // Initialize USB serial
    SerialUSB.begin();
    
    // Optional: Wait for serial connection with timeout
    uint32_t startTime = millis();
    while (!SerialUSB && millis() - startTime < 3000) {
        delay(10);
    }
    
    SerialUSB.println("MatekH743 initialized!");
    SerialUSB.println("LED blinking started...");
}

void loop() {
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, LOW);
    SerialUSB.println("LED1 ON, LED2 OFF");
    delay(500);
    
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, HIGH);
    SerialUSB.println("LED1 OFF, LED2 ON");
    delay(500);
}