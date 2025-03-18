#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include <SPI.h>
#include "MatekH743_Pinout.h"  // Defines UART2_RX_PIN and UART2_TX_PIN
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>
#include <SoftwareSerial.h>

// Structure to hold basic GPS data.
// Latitude and longitude are returned as degrees * 10^-7,
// Altitude is returned in millimeters,
// SIV indicates the number of satellites in view,
// millisecond contains the millisecond portion,
// minute and second provide additional time information.
struct GPSData {
  long latitude;     // e.g., 374221234 means 37.4221234° (multiply by 10^-7)
  long longitude;    // e.g., -122084567 means -122.084567° (multiply by 10^-7)
  long altitude;     // in millimeters
  byte SIV;          // Number of satellites in view
  int millisecond;   // Millisecond portion of the timestamp
  int minute;        // Minute portion of the timestamp
  int second;        // Second portion of the timestamp
};

namespace GPSModule {

  // Create a SoftwareSerial instance for communication.
  // RX is UART2_RX_PIN and TX is UART2_TX_PIN as defined in MatekH743_Pinout.h.
  inline SoftwareSerial& getSerial() {
    static SoftwareSerial mySerial(UART2_RX_PIN, UART2_TX_PIN);
    return mySerial;
  }

  // Create a GNSS object instance.
  inline SFE_UBLOX_GNSS& getGNSS() {
    static SFE_UBLOX_GNSS myGNSS;
    return myGNSS;
  }

  // (Optional) A timer to track update intervals if needed.
  inline long& getLastTime() {
    static long lastTime = 0;
    return lastTime;
  }
  
} // namespace GPSModule

// Initialize the GPS module using SoftwareSerial.
// This function attempts to synchronize with the GNSS module at 38400 baud first,
// then at 9600 baud if necessary, configures the module for UBX-only output,
// and sets the navigation update rate to 10 Hz.
inline void initGPS() {
  Serial.println("SparkFun u-blox Example");

  // Loop until the GNSS module synchronizes.
  do {
    Serial.println("GNSS: trying 38400 baud");
    GPSModule::getSerial().begin(38400);
    if (GPSModule::getGNSS().begin(GPSModule::getSerial()) == true)
      break;
    
    delay(100);
    Serial.println("GNSS: trying 9600 baud");
    GPSModule::getSerial().begin(9600);
    if (GPSModule::getGNSS().begin(GPSModule::getSerial()) == true) {
      Serial.println("GNSS: connected at 9600 baud, switching to 38400");
      GPSModule::getGNSS().setSerialRate(38400);
      delay(100);
      break;
    } else {
      delay(2000); // Wait a bit before trying again
    }
  } while (true);
  
  Serial.println("GNSS serial connected");

  // Configure the GNSS module:
  // - Set UART1 output to UBX-only to reduce NMEA noise.
  // - Set the navigation update frequency to 10 Hz.
  GPSModule::getGNSS().setUART1Output(COM_TYPE_UBX);
  GPSModule::getGNSS().setNavigationFrequency(10);
  byte rate = GPSModule::getGNSS().getNavigationFrequency();
  Serial.print("Current update rate: ");
  Serial.println(rate);

  GPSModule::getGNSS().saveConfiguration(); // Save settings to flash
}

// Read and return the current GPS data.
// This function calls getPVT() to check for a fresh navigation solution.
// If new data is available, it updates and returns a static GPSData structure.
inline GPSData readGPS() {
  static GPSData data = {0, 0, 0, 0, 0, 0, 0};  // Stores the last valid GPS reading
  
  if (GPSModule::getGNSS().getPVT()) {
    data.latitude    = GPSModule::getGNSS().getLatitude();
    data.longitude   = GPSModule::getGNSS().getLongitude();
    data.altitude    = GPSModule::getGNSS().getAltitude();
    data.SIV         = GPSModule::getGNSS().getSIV();
    data.millisecond = GPSModule::getGNSS().getMillisecond();
    data.minute      = GPSModule::getGNSS().getMinute();
    data.second      = GPSModule::getGNSS().getSecond();
  }
  return data;
}

#endif // GPS_H
