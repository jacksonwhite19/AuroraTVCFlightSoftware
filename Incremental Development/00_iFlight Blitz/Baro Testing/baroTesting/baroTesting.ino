#include <Arduino.h>
#include <Wire.h>
#include "BlitzH743.h"
#include <Dps3xx.h>

#define DPS310_ADDR 0x76

TwoWire myI2C2(PIN_I2C2_SDA, PIN_I2C2_SCL);
Dps3xx dps310;

float baselinePressure = 0.0;
bool baselineSet = false;
unsigned long zeroTime = 0;

void setup() {
  Serial.begin(115200);
  uint32_t startTime = millis();
  while (!Serial && millis() - startTime < 3000) delay(10);

  Serial.println("🔍 DPS310 Altitude Plotter");

  myI2C2.begin();
  dps310.begin(myI2C2, DPS310_ADDR);
  Serial.println("✅ DPS310 initialized");

  uint8_t productID = dps310.getProductId();
  Serial.print("📦 Product ID: 0x");
  Serial.println(productID, HEX);

  zeroTime = millis();
  Serial.println("Time (ms), Altitude (ft)");  // CSV header for plotting
}

void loop() {
  float pressure_pa = 0;
  unsigned long now = millis();

  if (dps310.measurePressureOnce(pressure_pa) == 0) {

    // After 30s, lock in baseline pressure once
    if (!baselineSet && (now - zeroTime > 30000)) {
      baselinePressure = pressure_pa;
      baselineSet = true;
      Serial.println("📍 Baseline pressure locked");
    }

    float altitude_ft = 0.0;
    if (baselineSet) {
      // Compute relative altitude from locked pressure
      float relPressureRatio = pressure_pa / baselinePressure;
      altitude_ft = 44330.0 * (1.0 - pow(relPressureRatio, 0.1903)) * 3.28084;
    }

    // Output time and altitude in CSV format
    Serial.print(now);
    Serial.print(", ");
    Serial.println(altitude_ft);
  } else {
    Serial.println("❌ Pressure read error");
  }

  delay(100);  // ~10 Hz sampling
}
