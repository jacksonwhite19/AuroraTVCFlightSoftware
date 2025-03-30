#include "MatekH743_Pinout.h"  // Defines UART7_TX_PIN (PE8), UART7_RX_PIN (PE7), and UART7_BASE
#include <HardwareSerial.h>

// Create a HardwareSerial instance for UART7 using its base address and assigned pins.
HardwareSerial mySerial7(UART7_BASE, UART7_RX_PIN, UART7_TX_PIN);

void setup() {
  Serial.begin(115200);
  while (!Serial) { }
  Serial.println("Hardware Serial test on UART7 with manual pin configuration");

  mySerial7.begin(9600);  // Ensure this baud rate matches your XBee settings
  Serial.println("mySerial7 initialized at 9600 baud");
}

void loop() {
  static unsigned long msgCount = 0;
  msgCount++;

  // Create a simple C-style string for the message.
  char message[100];
  snprintf(message, sizeof(message), "Hello from FlightModule, msg #%lu", msgCount);

  // Transmit the message over UART7
  mySerial7.println(message);
  
  // Debug output on USB Serial
  Serial.print("Loop iteration ");
  Serial.print(msgCount);
  Serial.print(" - Sent: ");
  Serial.println(message);

  delay(1000);
}
