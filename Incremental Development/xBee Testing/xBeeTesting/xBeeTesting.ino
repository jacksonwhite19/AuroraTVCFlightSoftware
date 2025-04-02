#include "MatekH743_Pinout.h"  // Defines UART7_TX_PIN (PE8) and UART7_RX_PIN (PE7)
#include <SoftwareSerial.h>
SoftwareSerial XBee(PD6, PD5); // RX, TX

void setup() {
  Serial.begin(9600);                // Start communication with the PC for debugging
  XBee.begin(9600);                  // Start communication with the XBee module
 
  randomSeed(analogRead(0));         // Seed the random number generator for varied results
}
 
void loop() {
  int randomNumber = random(256);    // Generate a random number between 0 and 255
  
  XBee.print('<');                   // Start of transmission marker
  XBee.print(randomNumber);          // Send the randomly generated number
  XBee.println('>');                 // End of transmission marker
 
  Serial.print("Sent number: ");     // Debugging output to Serial Monitor
  Serial.println(randomNumber);
 
  delay(1000);                       // Delay between sends to avoid flooding
}