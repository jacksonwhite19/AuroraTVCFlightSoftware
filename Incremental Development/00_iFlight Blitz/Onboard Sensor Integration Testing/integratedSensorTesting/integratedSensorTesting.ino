#include "BlitzH743.h"
#include "barometer.h"
#include "imu.h"
#include <SPI.h>
void setup() {
  Serial.begin(115200);
  SerialUSB.begin(115200);

  baro::begin();
  imu::begin();

  Serial.println("Timestamp(ms), Pressure(Pa), Altitude(ft)");
  SerialUSB.println("ax\tay\taz\tgx\tgy\tgz\ttemp_C");
}

void loop() {
  // Barometer
  baro::data baro = baro::read();
  if (baro.valid) {
    Serial.print(baro.timestamp_ms);
    Serial.print(" ms, Pressure: ");
    Serial.print(baro.pressure_pa);
    Serial.print(" Pa, Altitude: ");
    Serial.print(baro.altitude_ft);
    Serial.println(" ft");
  } else {
    Serial.println("Barometer data invalid");
  }

  // IMU
  imu::data imu = imu::read();
  if (imu.valid) {
    SerialUSB.print(imu.ax, 6); SerialUSB.print("\t");
    SerialUSB.print(imu.ay, 6); SerialUSB.print("\t");
    SerialUSB.print(imu.az, 6); SerialUSB.print("\t");
    SerialUSB.print(imu.gx, 6); SerialUSB.print("\t");
    SerialUSB.print(imu.gy, 6); SerialUSB.print("\t");
    SerialUSB.print(imu.gz, 6); SerialUSB.print("\t");
    SerialUSB.println(imu.temp_C, 6);
  } else {
    SerialUSB.println("IMU data invalid");
  }

  delay(100);
}
