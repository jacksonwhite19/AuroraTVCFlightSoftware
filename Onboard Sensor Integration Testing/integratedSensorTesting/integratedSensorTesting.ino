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
  
  // Initialize sensors
  initIMU();
  initBarometer();
}

void loop() {
  // Read sensor data from the IMU and Barometer
  IMUData imuData = readIMU();
  BarometerData baroData = readBarometer();

  // Print IMU data (accelerometer, gyroscope, and temperature)
  SerialUSB.print(imuData.ax, 6);
  SerialUSB.print("\t");
  SerialUSB.print(imuData.ay, 6);
  SerialUSB.print("\t");
  SerialUSB.print(imuData.az, 6);
  SerialUSB.print("\t");
  SerialUSB.print(imuData.gx, 6);
  SerialUSB.print("\t");
  SerialUSB.print(imuData.gy, 6);
  SerialUSB.print("\t");
  SerialUSB.print(imuData.gz, 6);
  SerialUSB.print("\t");
  SerialUSB.print(imuData.temp, 6);
  SerialUSB.print("\t");

  // Print Barometer data (pressure and temperature)
  SerialUSB.print("Pressure: ");
  SerialUSB.print(baroData.pressure);
  SerialUSB.print(" Pa, Temp: ");
  SerialUSB.print(baroData.temperature);
  SerialUSB.println(" C");

  delay(100);
}
