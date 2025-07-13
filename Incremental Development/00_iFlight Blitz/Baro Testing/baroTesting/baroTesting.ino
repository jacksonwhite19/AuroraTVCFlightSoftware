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

// EMA filter setup
float smoothedAltitude = 0.0;
const float alpha = 0.05;  // 0.05 = strong smoothing, adjust as needed

void setup() {
  Serial.begin(115200);
  uint32_t startTime = millis();
  while (!Serial && millis() - startTime < 3000) delay(10);

  Serial.println("🔍 DPS310 Altitude (ft) with EMA Filter");

  myI2C2.begin();
  dps310.begin(myI2C2, DPS310_ADDR);
  Serial.println("✅ DPS310 initialized");

  uint8_t productID = dps310.getProductId();
  Serial.print("📦 Product ID: 0x");
  Serial.println(productID, HEX);

  zeroTime = millis();
  Serial.println("Time (ms), Altitude (ft)");
}

void loop() {
  float pressure_pa = 0;
  unsigned long now = millis();

  if (dps310.measurePressureOnce(pressure_pa) == 0) {
    // Set baseline after 30 seconds
    if (!baselineSet && (now - zeroTime > 30000)) {
      baselinePressure = pressure_pa;
      baselineSet = true;
      Serial.println("📍 Baseline pressure locked");
    }

    float altitude_ft = 0.0;
    if (baselineSet) {
      float ratio = pressure_pa / baselinePressure;
      float altitude_m = 44330.0 * (1.0 - pow(ratio, 0.1903));
      altitude_ft = altitude_m * 3.28084;

      // Apply exponential moving average
      smoothedAltitude = alpha * altitude_ft + (1.0 - alpha) * smoothedAltitude;

      Serial.print(now);
      Serial.print(", ");
      Serial.println(smoothedAltitude);
    } else {
      // Output 0 before baseline is locked
      Serial.print(now);
      Serial.println(", 0");
    }
  } else {
    Serial.println("❌ Pressure read error");
  }

  delay(100);
}
