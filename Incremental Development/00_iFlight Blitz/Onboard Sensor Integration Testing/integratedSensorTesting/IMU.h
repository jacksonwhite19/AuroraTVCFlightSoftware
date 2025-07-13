#ifndef IMU_H
#define IMU_H

#include "ICM42688.h"
#include "BlitzH743.h"
#include <SPI.h>

namespace imu {

  struct data {
    float ax, ay, az;
    float gx, gy, gz;
    float temp_C;
    unsigned long timestamp_ms;
    bool valid;
  };

  // ⚠️ Don't redeclare spi1 here
  ICM42688 sensor(::spi1, PIN_IMU1_CS);  // explicitly reference global spi1
  bool initialized = false;

  void begin() {
    ::spi1.begin();  // same here
    int status = sensor.begin();
    if (status < 0) {
      while (1) {}
    }
    initialized = true;
  }

  data read() {
    data imuData;
    imuData.timestamp_ms = millis();
    imuData.valid = false;

    if (!initialized) return imuData;

    sensor.getAGT();
    imuData.ax = sensor.accX();
    imuData.ay = sensor.accY();
    imuData.az = sensor.accZ();
    imuData.gx = sensor.gyrX();
    imuData.gy = sensor.gyrY();
    imuData.gz = sensor.gyrZ();
    imuData.temp_C = sensor.temp();
    imuData.valid = true;
    return imuData;
  }

}

#endif
