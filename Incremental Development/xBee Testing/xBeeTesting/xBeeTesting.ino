#include <SoftwareSerial.h>
#include "MatekH743_Pinout.h"  // This file defines UART7_TX_PIN (PE8) and UART7_RX_PIN (PE7)

// Create a SoftwareSerial instance on UART7 pins: 
// Note: The first parameter is the RX pin, the second is the TX pin.
SoftwareSerial flightSerial(UART7_RX_PIN, UART7_TX_PIN);

void setup() {
  // Initialize USB serial for debugging on your computer.
  Serial.begin(115200);
  while (!Serial) { } // Wait for the Serial Monitor to connect

  Serial.println("FlightModule Serial Test Starting...");

  // Initialize the SoftwareSerial port for UART7.
  // Ensure that the baud rate (here, 9600) matches your XBee configuration.
  flightSerial.begin(9600);
}

void loop() {
  // Send a simple message over UART7 to the groundstation.
  flightSerial.println("Hello from FlightModule");

  // Also print to USB serial for debugging purposes.
  Serial.println("Sent: Hello from FlightModule");

  // Wait 1 second before sending the next message.
  delay(1000);
}
