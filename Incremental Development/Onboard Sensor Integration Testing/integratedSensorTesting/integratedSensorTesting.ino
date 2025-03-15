#include <SPI.h>
#include "MatekH743_Pinout.h"
#include "IMU.h"
#include "Barometer.h"
#include "Telemetry.h"

void setup() {
  SerialUSB.begin(115200);
  uint32_t startTime = millis();
  while (!SerialUSB && millis() - startTime < 3000) {
    delay(10);
  }
  
  // Optional header for debugging; this can be removed for production telemetry.
  SerialUSB.println("=== Telemetry Data Output ===");
  SerialUSB.println("Format: $TELE,<ax>,<ay>,<az>,<gx>,<gy>,<gz>,<temp>,<pressure>,<baro_temp>*CS");
  SerialUSB.println();

  // Initialize sensors
  initIMU();
  initBarometer();
}

void loop() {
  // Read sensor data from IMU and Barometer
  IMUData imuData = readIMU();
  BarometerData baroData = readBarometer();

  // Create a telemetry packet using the sensor values
  String telemetryPacket = createTelemetryPacket(
    imuData.ax, imuData.ay, imuData.az,
    imuData.gx, imuData.gy, imuData.gz,
    imuData.temp,
    baroData.pressure, baroData.temperature
  );

  // Transmit the telemetry packet over SerialUSB (to the xBee module)
  SerialUSB.println(telemetryPacket);

  delay(50);
}
