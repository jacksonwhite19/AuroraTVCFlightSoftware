#include <SPI.h>
#include <Wire.h>
#include "MatekH743_Pinout.h"    // Board pin definitions (defines I2C2_SDA_PIN, I2C2_SCL_PIN, SerialUSB, etc.)
#include <Adafruit_DPS310.h>     // Adafruit DPS310 library

// Create a TwoWire instance for I2C2 using board-defined pins
TwoWire myI2C2(I2C2_SDA_PIN, I2C2_SCL_PIN);

// Create an instance of the DPS310 sensor
Adafruit_DPS310 dps;

void setup() {
  // Initialize USB serial communication
  SerialUSB.begin(115200);
  uint32_t startTime = millis();
  while (!SerialUSB && millis() - startTime < 3000) {
    delay(10);
  }
  SerialUSB.println("DPS310 test starting...");

  // Begin I2C on our custom bus (I2C2)
  myI2C2.begin();

  // Initialize the DPS310 sensor using I2C mode.
  // Note: The library uses begin_I2C() to initialize over I2C.
  if (!dps.begin_I2C(&myI2C2)) {
    SerialUSB.println("Could not find a valid DPS310 sensor, check wiring!");
    while (1) { delay(10); }
  }
  SerialUSB.println("DPS310 sensor found!");

  // Optionally, configure sensor parameters (oversampling, filter, etc.) via library methods if available.
}

void loop() {
  // Read pressure in Pascals and temperature in Celsius using library functions.
  float pressure = dps.pressure();
  float temperature = dps.temperature();

  // Print the measurements to SerialUSB
  SerialUSB.print("Pressure: ");
  SerialUSB.print(pressure);
  SerialUSB.print(" Pa, Temperature: ");
  SerialUSB.print(temperature);
  SerialUSB.println(" C");

  delay(1000);
}
