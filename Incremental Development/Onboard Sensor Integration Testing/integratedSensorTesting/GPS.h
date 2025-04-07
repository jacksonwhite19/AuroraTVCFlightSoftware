#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include <SPI.h>
#include "MatekH743_Pinout.h" // Defines UART2_RX_PIN and UART2_TX_PIN
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>
#include <SoftwareSerial.h>

// GPS data struct
struct GPSData {
  long latitude;
  long longitude;
  long altitude;
  byte SIV;
  byte minute;
  byte second;
  int millisecond;
};

// Global GPS data instance
GPSData gpsData;

// GNSS and Serial instances
SFE_UBLOX_GNSS myGNSS;
SoftwareSerial mySerial(UART2_RX_PIN, UART2_TX_PIN); // RX, TX

// Initialize GPS
void initGPS() {
  while (!Serial); // Wait for USB if needed

  // Try 38400 baud first
  do {
    Serial.println("GNSS: trying 38400 baud");
    mySerial.begin(38400);
    if (myGNSS.begin(mySerial)) break;

    delay(100);
    Serial.println("GNSS: trying 9600 baud");
    mySerial.begin(9600);
    if (myGNSS.begin(mySerial)) {
      Serial.println("GNSS: connected at 9600 baud, switching to 38400");
      myGNSS.setSerialRate(38400);
      delay(100);
    } else {
      delay(2000);
    }
  } while (1);

  Serial.println("GNSS serial connected");

  myGNSS.setUART1Output(COM_TYPE_UBX);     // Use UBX messages only
  myGNSS.setNavigationFrequency(50);       // 10 Hz update rate
  myGNSS.saveConfiguration();              // Save to flash
}

// Read GPS data
GPSData readGPS() {
  if (myGNSS.getPVT()) {
    gpsData.latitude     = myGNSS.getLatitude();
    gpsData.longitude    = myGNSS.getLongitude();
    gpsData.altitude     = myGNSS.getAltitude();
    gpsData.SIV          = myGNSS.getSIV();
    gpsData.minute       = myGNSS.getMinute();
    gpsData.second       = myGNSS.getSecond();
    gpsData.millisecond  = myGNSS.getMillisecond();
  }
  return gpsData; //return a copy of the updated struct
}

#endif // GPS_H
