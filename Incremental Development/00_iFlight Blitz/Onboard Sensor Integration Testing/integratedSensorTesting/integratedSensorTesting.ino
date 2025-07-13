#include "BlitzH743.h"
#include "barometer.h"

void setup() {
  Serial.begin(115200);
  baro::begin();
}

void loop() {
  baro::data d = baro::read();
  if (d.valid) {
    Serial.print(d.timestamp_ms);
    Serial.print(" ms, Pressure: ");
    Serial.print(d.pressure_pa);
    Serial.print(" Pa, Altitude: ");
    Serial.print(d.altitude_ft);
    Serial.println(" ft");
  } else {
    Serial.println("Barometer data invalid");
  }

  delay(100);
}
