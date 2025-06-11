// as of 4/7: code works well, need to integrate LIDAR into it. all other sensors functioning normally.
// has a psuedo packet telem system worked out, this seems like a problem that should be addressed
// once everything else is integrated and I know exactly how much data I need to transmit.

#include "MatekH743_Pinout.h"
#include <SoftwareSerial.h>
#include "IMU.h"
#include "Barometer.h"
#include "Telemetry.h"
#include "GPS.h"   // Header-only GPS library

SoftwareSerial XBee(PC7, PC6); // RX, TX

void setup() {
  XBee.begin(115200);
  Serial.begin(115200);

  Serial.println("=== Telemetry Data Output ===");
  Serial.println("Format: $TELE,<ax>,<ay>,<az>,<gx>,<gy>,<gz>,<temp>,<pressure>,<baro_temp>,<lat>,<lon>,<alt>,<siv>,<min>,<sec>,<ms>*CS");
  Serial.println();

  initIMU();
  initBarometer();
  initGPS();
}

void loop() {
  IMUData imuData = readIMU();
  BarometerData baroData = readBarometer();
  GPSData gpsData = readGPS();

  String telemetryPacket = createTelemetryPacket(
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
