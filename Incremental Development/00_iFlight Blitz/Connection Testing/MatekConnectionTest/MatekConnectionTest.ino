#include "BlitzH743.h"  // Make sure this is in your include path

void setup() {
  // Start UART1 for serial output
  Serial.begin(115200); // UART1 = TX: PA9, RX: PA10

  // Configure test pins
  pinMode(LED_STRIP_PIN, OUTPUT);
  pinMode(BEEPER_PIN, OUTPUT);

  // Initial state
  digitalWrite(LED_STRIP_PIN, LOW);
  digitalWrite(BEEPER_PIN, LOW);

  Serial.println("BlitzH743 Test Initialized");
}

void loop() {
  Serial.println("Blink!");
  
  // Toggle LED and Beeper
  digitalWrite(LED_STRIP_PIN, HIGH);
  digitalWrite(BEEPER_PIN, HIGH);
  delay(200);

  digitalWrite(LED_STRIP_PIN, LOW);
  digitalWrite(BEEPER_PIN, LOW);
  delay(800);
}
