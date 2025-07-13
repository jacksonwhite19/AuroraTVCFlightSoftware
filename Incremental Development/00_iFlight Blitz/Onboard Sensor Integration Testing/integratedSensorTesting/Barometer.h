#ifndef BAROMETER_H
#define BAROMETER_H

#include <Arduino.h>
#include <Wire.h>
#include "BlitzH743.h"
#include <Dps3xx.h>

#define DPS310_ADDR 0x76

namespace baro {

  struct data {
    float pressure_pa;
    float altitude_ft;
    unsigned long timestamp_ms;
    bool valid;
  };

  TwoWire i2c(PIN_I2C2_SDA, PIN_I2C2_SCL);
  Dps3xx sensor;

  float baselinePressure = 0.0;
  bool baselineSet = false;
  unsigned long zeroTime = 0;

  void begin() {
    i2c.begin();
    sensor.begin(i2c, DPS310_ADDR);
    zeroTime = millis();
  }

  data read() {
    data baroData;
    baroData.timestamp_ms = millis();
    baroData.pressure_pa = 0.0;
    baroData.altitude_ft = 0.0;
    baroData.valid = false;

    float pressure_pa = 0;
    if (sensor.measurePressureOnce(pressure_pa) == 0) {
      if (!baselineSet && (baroData.timestamp_ms - zeroTime > 30000)) {
        baselinePressure = pressure_pa;
        baselineSet = true;
      }

      baroData.pressure_pa = pressure_pa;
      baroData.valid = true;

      if (baselineSet) {
        float ratio = pressure_pa / baselinePressure;
        float altitude_m = 44330.0 * (1.0 - pow(ratio, 0.1903));
        baroData.altitude_ft = altitude_m * 3.28084;
      } else {
        baroData.altitude_ft = 0.0;
      }
    }

    return baroData;
  }
}

#endif
