#include <SoftwareSerial.h>
#include "MatekH743_Pinout.h"

// TFMini Plus is connected to UART7: RX = PE7, TX = PE8
SoftwareSerial tfminiSerial(UART7_RX_PIN, UART7_TX_PIN);  // RX, TX

void setup() {
  Serial.begin(115200);
  while (!Serial);  // Wait for Serial Monitor/Plotter to be ready

  tfminiSerial.begin(115200);  // TFMini default baud rate
  delay(1000);  // Allow time for sensor to stabilize
}

void loop() {
  static uint8_t buf[9];
  static int i = 0;

  while (tfminiSerial.available()) {
    uint8_t c = tfminiSerial.read();

    if (i == 0 && c != 0x59) continue;
    if (i == 1 && c != 0x59) { i = 0; continue; }

    buf[i++] = c;

    if (i == 9) {
      uint16_t distance = buf[2] + (buf[3] << 8);
      uint16_t strength = buf[4] + (buf[5] << 8);
      uint8_t checksum = 0;
      for (int j = 0; j < 8; j++) checksum += buf[j];

      if (checksum == buf[8]) {
        // Output tab-separated values for Serial Plotter
        Serial.print(distance);
        Serial.print('\t');
        Serial.println(strength);
      }

      i = 0;
    }
  }
}
