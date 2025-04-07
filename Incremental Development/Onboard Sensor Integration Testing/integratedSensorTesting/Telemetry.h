#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <Arduino.h>
#include "MatekH743_Pinout.h"

// Function: calculates checksum by XOR-ing every character in the sentence.
// The input should be the string without the starting '$'.
inline String calculateChecksum(const String &sentence) {
  byte cs = 0;
  for (size_t i = 0; i < sentence.length(); i++) {
    cs ^= sentence.charAt(i);
  }
  String hexStr = String(cs, HEX);
  if (hexStr.length() < 2) {
    hexStr = "0" + hexStr;
  }
  return hexStr;
}

// Function: creates a telemetry packet in an NMEA-like format
// Returns the formatted telemetry packet as a String.
String createTelemetryPacket(float ax, float ay, float az,
                             float gx, float gy, float gz,
                             float imuTemp,
                             float baroPressure, float baroTemp,
                             long gpsLat, long gpsLon, long gpsAlt,
                             byte gpsSIV, int gpsMin, int gpsSec, int gpsMs) {
  String packet = "$TELE,";
  packet += String(ax, 2) + ",";
  packet += String(ay, 2) + ",";
  packet += String(az, 2) + ",";
  packet += String(gx, 2) + ",";
  packet += String(gy, 2) + ",";
  packet += String(gz, 2) + ",";
  packet += String(imuTemp, 2) + ",";
  packet += String(baroPressure, 2) + ",";
  packet += String(baroTemp, 2) + ",";
  packet += String(gpsLat) + ",";
  packet += String(gpsLon) + ",";
  packet += String(gpsAlt) + ",";
  packet += String(gpsSIV) + ",";
  packet += String(gpsMin) + ",";
  packet += String(gpsSec) + ",";
  packet += String(gpsMs);

  // Calculate checksum on the packet excluding the '$'
  String cs = calculateChecksum(packet.substring(1));
  packet += "*" + cs;

  return packet;
}

#endif // TELEMETRY_H
