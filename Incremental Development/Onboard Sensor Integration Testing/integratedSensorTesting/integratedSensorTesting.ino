#include "MatekH743_Pinout.h"
#include "IMU.h"
#include "Barometer.h"
#include "Telemetry.h"
#include "GPS.h"   // Include the header-only GPS library

void setup() {
  SerialUSB.begin(115200);
  // Wait for SerialUSB to initialize...
  
  // Print telemetry header (update format as needed)
  SerialUSB.println("=== Telemetry Data Output ===");
  SerialUSB.println("Format: $TELE,<ax>,<ay>,<az>,<gx>,<gy>,<gz>,<temp>,<pressure>,<baro_temp>,<lat>,<lon>,<alt>*CS");
  SerialUSB.println();
  
  // Initialize sensors
  initIMU();
  initBarometer();
  initGPS();  // Initialize GPS via the header-only functions
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
    gpsData.latitude, gpsData.longitude, gpsData.altitude
  );

  SerialUSB.println(telemetryPacket);
  delay(50);
}
