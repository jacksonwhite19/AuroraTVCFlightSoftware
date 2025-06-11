#include <Wire.h>
#include <BlitzH743.h>
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>

SFE_UBLOX_GNSS gps;
HardwareSerial GPSSerial(PIN_SERIAL4_RX, PIN_SERIAL4_TX);  // PB8 = RX, PB9 = TX

void initializeGPS();
void readGPS();

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  initializeGPS();
}

void loop() {

  readGPS();
}


void initializeGPS() {
  GPSSerial.begin(115200); // Use 115200 if confirmed in Betaflight
  if (!gps.begin(GPSSerial)) {
    Serial.println("GPS not detected. Check wiring and baud rate.");
    while (1);
  }

  Serial.println("GPS initialized!");

  gps.setI2COutput(COM_TYPE_UBX); // Just UBX messages
  gps.setNavigationFrequency(5); // 5Hz update rate
  gps.setAutoPVT(true);          // Enable automatic position updates
}

void readGPS() {
  if (gps.getPVT()) {
    Serial.print("Lat: ");
    Serial.print(gps.getLatitude() / 1e7, 7);
    Serial.print(", Lon: ");
    Serial.print(gps.getLongitude() / 1e7, 7);
    Serial.print(", Alt: ");
    Serial.print(gps.getAltitude() / 1000.0);
    Serial.print(" m, SIV: ");
    Serial.println(gps.getSIV());
  }
}
