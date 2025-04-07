#include "MatekH743_Pinout.h"
#include <SoftwareSerial.h>
#include "IMU.h"
#include "Barometer.h"
#include "Telemetry.h"
#include "GPS.h"   // Include the header-only GPS library

SoftwareSerial XBee(PC7, PC6); // RX, TX

void setup() {
  XBee.begin(115200);
  Serial.begin(115200);
  // Wait for Serial to initialize...
  
  // Print telemetry header with updated GPS fields: SIV, minute, second, and millisecond
  Serial.println("=== Telemetry Data Output ===");
  Serial.println("Format: $TELE,<ax>,<ay>,<az>,<gx>,<gy>,<gz>,<temp>,<pressure>,<baro_temp>,<lat>,<lon>,<alt>,<siv>,<min>,<sec>,<ms>*CS");
  Serial.println();
  
  // Initialize sensors
  initIMU();
  initBarometer();
  initGPS();  // Initialize GPS via the header-only functions
}

void loop() {
  IMUData imuData = readIMU();
  BarometerData baroData = readBarometer();
  GPSData gpsData = readGPS();

  // Create a telemetry packet including the extra GPS fields:
  // GPS latitude, longitude, altitude, SIV, minute, second, and millisecond.
char telemetryPacket[200];
createTelemetryPacket(telemetryPacket, sizeof(telemetryPacket),
  imuData.ax, imuData.ay, imuData.az,
  imuData.gx, imuData.gy, imuData.gz,
  imuData.temp,
  baroData.pressure, baroData.temperature,
  gpsData.latitude, gpsData.longitude, gpsData.altitude,
  gpsData.SIV, gpsData.minute, gpsData.second, gpsData.millisecond
);
XBee.print(telemetryPacket);
Serial.println(telemetryPacket);
delay(10);
}
