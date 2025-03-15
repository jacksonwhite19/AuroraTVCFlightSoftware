#include <SPI.h>
#include "MatekH743_Pinout.h"
#include "IMU.h"
#include "Barometer.h"

void setup() {
  SerialUSB.begin(115200);
  uint32_t startTime = millis();
  while (!SerialUSB && millis() - startTime < 3000) {
    delay(10);
  }
  
  // Print header with format details
  SerialUSB.println("=== Sensor Data Output ===");
  SerialUSB.println("Format:");
  SerialUSB.println("[IMU] Acc: (ax, ay, az) | Gyro: (gx, gy, gz) | Temp: °C");
  SerialUSB.println("[Barometer] Pressure: Pa | Temp: °C");
  SerialUSB.println();
  
  // Initialize sensors
  initIMU();
  initBarometer();
}

void loop() {
  // Read sensor data from IMU and Barometer
  IMUData imuData = readIMU();
  BarometerData baroData = readBarometer();

  // Print formatted IMU data
  SerialUSB.print("[IMU] Acc: (");
  SerialUSB.print(imuData.ax, 2);
  SerialUSB.print(", ");
  SerialUSB.print(imuData.ay, 2);
  SerialUSB.print(", ");
  SerialUSB.print(imuData.az, 2);
  SerialUSB.print(")  |  Gyro: (");
  SerialUSB.print(imuData.gx, 2);
  SerialUSB.print(", ");
  SerialUSB.print(imuData.gy, 2);
  SerialUSB.print(", ");
  SerialUSB.print(imuData.gz, 2);
  SerialUSB.print(")  |  Temp: ");
  SerialUSB.print(imuData.temp, 2);
  SerialUSB.println(" °C");

  // Print formatted Barometer data
  SerialUSB.print("[Barometer] Pressure: ");
  SerialUSB.print(baroData.pressure, 2);
  SerialUSB.print(" Pa  |  Temp: ");
  SerialUSB.print(baroData.temperature, 2);
  SerialUSB.println(" °C");

  SerialUSB.println("------------------------------------------------------------------------------------------");
  delay(50);
}
