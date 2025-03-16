#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include <SPI.h>
#include "MatekH743_Pinout.h"  // Defines pin mappings (e.g., UART2_RX_PIN, UART2_TX_PIN)
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>
#include <SoftwareSerial.h>

// Structure to hold GPS data.
// Latitude and longitude are returned as degrees * 10^-7,
// Altitude is returned in millimeters,
// SIV indicates the number of satellites in view.
struct GPSData {
  long latitude;
  long longitude;
  long altitude;
  byte SIV;
};

namespace GPSModule {

  // Create a SoftwareSerial instance for communicating with the GNSS module.
  inline SoftwareSerial& getSerial() {
    static SoftwareSerial mySerial(UART2_RX_PIN, UART2_TX_PIN); // RX, TX
    return mySerial;
  }

  // Create a GNSS object instance.
  inline SFE_UBLOX_GNSS& getGNSS() {
    static SFE_UBLOX_GNSS myGNSS;
    return myGNSS;
  }

  // Timer to control update frequency.
  inline long& getLastTime() {
    static long lastTime = 0;
    return lastTime;
  }
  
} // namespace GPSModule

// Define the update interval in milliseconds.
const unsigned long GPS_UPDATE_INTERVAL_MS = 50;  // Update every 50ms

// Initialize the GPS module. This function sets up the serial connection,
// synchronizes with the GNSS module, and configures output formats.
inline void initGPS() {
  // For debugging: initialize the default Serial port.
  Serial.begin(115200);
  while (!Serial); // Wait until the serial monitor is open
  Serial.println("SparkFun u-blox Example");

  bool connected = false;
  // Try to connect at 38400 baud first, then at 9600 baud.
  do {
    Serial.println("GNSS: trying 38400 baud");
    GPSModule::getSerial().begin(38400);
    if (GPSModule::getGNSS().begin(GPSModule::getSerial()) == true) {
      connected = true;
      break;
    }
    delay(100);
    Serial.println("GNSS: trying 9600 baud");
    GPSModule::getSerial().begin(9600);
    if (GPSModule::getGNSS().begin(GPSModule::getSerial()) == true) {
      Serial.println("GNSS: connected at 9600 baud, switching to 38400");
      GPSModule::getGNSS().setSerialRate(38400);
      delay(100);
      connected = true;
      break;
    } else {
      delay(2000); // Wait a bit before trying again
    }
  } while (!connected);

  Serial.println("GNSS serial connected");

  // Configure the GNSS module to output UBX protocol only.
  GPSModule::getGNSS().setUART1Output(COM_TYPE_UBX);
  GPSModule::getGNSS().setI2COutput(COM_TYPE_UBX);
  GPSModule::getGNSS().saveConfiguration(); // Save settings to flash
}

// Read and return the current GPS data.
// This function updates the data based on the defined update interval.
inline GPSData readGPS() {
  static GPSData lastData = {0, 0, 0, 0};  // Stores the last valid GPS reading
  
  // Update only if more than GPS_UPDATE_INTERVAL_MS have passed
  if (millis() - GPSModule::getLastTime() > GPS_UPDATE_INTERVAL_MS) {
    GPSModule::getLastTime() = millis();
    lastData.latitude  = GPSModule::getGNSS().getLatitude();
    lastData.longitude = GPSModule::getGNSS().getLongitude();
    lastData.altitude  = GPSModule::getGNSS().getAltitude();
    lastData.SIV       = GPSModule::getGNSS().getSIV();
  }
  return lastData;
}

#endif // GPS_H
