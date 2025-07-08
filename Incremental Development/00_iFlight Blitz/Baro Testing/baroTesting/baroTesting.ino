#include <Arduino.h>
#include <Wire.h>
#include "BlitzH743.h"         // Your custom board file
#include <Dps3xx.h>            // Infineon XENSIV DPS3xx library

#define DPS310_ADDR 0x76

// Custom I2C bus for your board
TwoWire myI2C2(PIN_I2C2_SDA, PIN_I2C2_SCL);

// DPS310 instance
Dps3xx dps310;

void setup() {
  Serial.begin(115200);
  uint32_t startTime = millis();
  while (!Serial && millis() - startTime < 3000) delay(10);

  Serial.println("🔍 DPS310 Debug Test (Infineon XENSIV Library)");

  // Start I2C2
  myI2C2.begin();

  // Initialize sensor — returns void
  dps310.begin(myI2C2, DPS310_ADDR);
  Serial.println("✅ DPS310 initialized");

  // Get product ID (returns directly)
  uint8_t productID = dps310.getProductId();
  Serial.print("📦 Product ID: 0x");
  Serial.println(productID, HEX);

  // Optionally configure oversampling
  // dps310.setPresOversampling(DPS310_8X);
  // dps310.setTempOversampling(DPS310_8X);
}

void loop() {
  float temperature = 0, pressure = 0;
  int16_t status;

  // Read temperature
  status = dps310.measureTempOnce(temperature);
  if (status == 0) {
    Serial.print("🌡️ Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C, ");
  } else {
    Serial.print("❌ Temp read error (code ");
    Serial.print(status);
    Serial.print("), ");
  }

  // Read pressure
  status = dps310.measurePressureOnce(pressure);
  if (status == 0) {
    Serial.print("🌪️ Pressure: ");
    Serial.print(pressure);
    Serial.println(" Pa");
  } else {
    Serial.print("❌ Pressure read error (code ");
    Serial.print(status);
    Serial.println(")");
  }

  delay(500);
}
