#include <SPI.h>
#include <Arduino.h>
#include <Wire.h>
#include "MatekH743_Pinout.h"  // Board pin definitions (ensure the filename matches your working LED example)

#define DPS310_ADDR 0x77  // I2C address for DPS310

// Create a TwoWire instance for I2C2 using SDA/SCL pins from the board file.
// We use a custom name to avoid conflicts with existing definitions.
TwoWire myI2C2(I2C2_SDA_PIN, I2C2_SCL_PIN);

// Function to initialize the DPS310 sensor
bool initDPS310() {
  // Reset the sensor: write 0x89 to register 0x0C (see datasheet)
  myI2C2.beginTransmission(DPS310_ADDR);
  myI2C2.write(0x0C);  // Reset register
  myI2C2.write(0x89);  // Reset command
  myI2C2.endTransmission();
  delay(100);  // Allow time for reset
  
  // Read product ID from register 0x0D to verify communication
  myI2C2.beginTransmission(DPS310_ADDR);
  myI2C2.write(0x0D);
  myI2C2.endTransmission();
  myI2C2.requestFrom(DPS310_ADDR, (uint8_t)1);
  if (myI2C2.available() < 1) {
    return false;
  }
  uint8_t productId = myI2C2.read();
  SerialUSB.print("DPS310 Product ID: ");
  SerialUSB.println(productId, HEX);
  
  // Configure sensor registers (example settings; adjust per your application)
  // For example, set oversampling and filter settings.
  myI2C2.beginTransmission(DPS310_ADDR);
  myI2C2.write(0x06);  // Pressure configuration register
  myI2C2.write(0x20);  // Example configuration value
  myI2C2.endTransmission();
  
  myI2C2.beginTransmission(DPS310_ADDR);
  myI2C2.write(0x07);  // Temperature configuration register
  myI2C2.write(0xA0);  // Example configuration value
  myI2C2.endTransmission();
  
  return true;
}

// Function to read 24-bit pressure and temperature values from DPS310
void readDPS310(int32_t &pressure, int32_t &temperature) {
  uint8_t buffer[6];
  
  // Assuming registers 0x00-0x02 hold pressure and 0x03-0x05 hold temperature
  myI2C2.beginTransmission(DPS310_ADDR);
  myI2C2.write(0x00);  // Starting register for reading data
  myI2C2.endTransmission();
  myI2C2.requestFrom(DPS310_ADDR, (uint8_t)6);
  for (uint8_t i = 0; i < 6; i++) {
    if (myI2C2.available()) {
      buffer[i] = myI2C2.read();
    }
  }
  
  // Combine bytes to form a 24-bit signed integer for pressure
  pressure = ((int32_t)buffer[0] << 16) | ((int32_t)buffer[1] << 8) | buffer[2];
  if (pressure & 0x800000) {  // sign extension if negative
    pressure |= 0xFF000000;
  }
  
  // Combine bytes to form a 24-bit signed integer for temperature
  temperature = ((int32_t)buffer[3] << 16) | ((int32_t)buffer[4] << 8) | buffer[5];
  if (temperature & 0x800000) {  // sign extension if negative
    temperature |= 0xFF000000;
  }
}

void setup() {
  // Initialize SerialUSB for output
  SerialUSB.begin(115200);
  uint32_t startTime = millis();
  while (!SerialUSB && millis() - startTime < 3000) {
    delay(10);
  }
  SerialUSB.println("Initializing DPS310 sensor...");
  
  // Initialize I2C2 interface
  myI2C2.begin();
  
  // Initialize the DPS310 sensor
  if (!initDPS310()) {
    SerialUSB.println("DPS310 initialization unsuccessful!");
    SerialUSB.println("Check sensor wiring and power.");
    while (1) { delay(10); }
  }
  SerialUSB.println("DPS310 sensor initialized successfully.");
  SerialUSB.println("Pressure, Temperature");
}

void loop() {
  int32_t pressure, temperature;
  
  // Read sensor data
  readDPS310(pressure, temperature);
  
  // Display the raw data over USB serial
  SerialUSB.print(pressure);
  SerialUSB.print(", ");
  SerialUSB.println(temperature);
  
  delay(1000);
}
