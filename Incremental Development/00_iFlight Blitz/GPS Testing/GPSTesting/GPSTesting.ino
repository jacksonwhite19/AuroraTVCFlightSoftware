#include <SparkFun_u-blox_GNSS_Arduino_Library.h>
SFE_UBLOX_GNSS myGNSS;

// Blitz H743: PB8 (RX), PB9 (TX) = UART4
HardwareSerial ss(PIN_SERIAL4_RX, PIN_SERIAL4_TX); // RX, TX

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Connecting to HGLRC M100 via UBX...");

  ss.begin(115200); // Most M100 modules default to 115200
  if (!myGNSS.begin(ss)) {
    Serial.println("GNSS not detected. Check wiring and baud rate.");
    while (1);
  }

  Serial.println("GNSS connected!");

  myGNSS.setUART1Output(COM_TYPE_UBX); // Use only UBX binary
  myGNSS.setNavigationFrequency(10);  // 10 Hz updates
  myGNSS.saveConfiguration();         // Save config to flash
}

void loop() {
  if (myGNSS.getPVT()) {
    // Convert raw data to readable values
    float lat = myGNSS.getLatitude() / 1e7;   // degrees
    float lon = myGNSS.getLongitude() / 1e7;  // degrees
    float alt = myGNSS.getAltitude() / 1000.0; // meters
    byte sats = myGNSS.getSIV();              // satellites in view

    Serial.print("Lat: ");
    Serial.print(lat, 7); // show full precision
    Serial.print("°  Lon: ");
    Serial.print(lon, 7);
    Serial.print("°  Alt: ");
    Serial.print(alt, 2);
    Serial.print(" m  SIV: ");
    Serial.println(sats);
  }
}
