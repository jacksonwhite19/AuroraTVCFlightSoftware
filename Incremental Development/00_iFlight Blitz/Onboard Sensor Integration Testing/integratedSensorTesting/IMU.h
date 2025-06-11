#ifndef IMU_H
#define IMU_H
#include <SPI.h>
#include "MatekH743_Pinout.h"
#include "ICM42688.h"
#include <Arduino.h>
#include "Telemetry.h"

// Create an instance of the ICM42688 sensor using spi1 and the defined chip-select pin.
ICM42688 imu(spi1, GYRO_1_CS_PIN);

// Structure to hold IMU sensor data
struct IMUData {
  float ax;
  float ay;
  float az;
  float gx;
  float gy;
  float gz;
  float temp;
};

// Function to initialize the IMU sensor (adapted from your IMUTesting.ino setup)
void initIMU() {
  SPI.begin();
  int status = imu.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while (1) {
      // Halt execution if the sensor fails to initialize.
      delay(10);
    }
  }
  Serial.println("ax,ay,az,gx,gy,gz,temp_C");
}

// Function to read data from the IMU sensor (adapted from your IMUTesting.ino loop)
IMUData readIMU() {
  IMUData data;
  imu.getAGT();
  data.ax = imu.accX();
  data.ay = imu.accY();
  data.az = imu.accZ();
  data.gx = imu.gyrX();
  data.gy = imu.gyrY();
  data.gz = imu.gyrZ();
  data.temp = (imu.temp() / 333.87) + 21.0;
  return data;
}

#endif // IMU_H

