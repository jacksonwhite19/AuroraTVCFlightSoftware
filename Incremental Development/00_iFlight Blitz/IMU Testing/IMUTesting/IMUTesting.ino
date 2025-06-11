#include "ICM42688.h"
#include "BlitzH743.h"
#include <SPI.h>

ICM42688 IMU(spi1, PIN_IMU1_CS);

void setup() {
  // SerialUSB to display data
  SerialUSB.begin(115200);
  
  // Optional: Wait for serial connection with timeout
    uint32_t startTime = millis();
    while (!SerialUSB && millis() - startTime < 3000) {
        delay(10);
    }

  // start communication with IMU
  int status = IMU.begin();
  if (status < 0) {
    SerialUSB.println("IMU initialization unsuccessful");
    SerialUSB.println("Check IMU wiring or try cycling power");
    SerialUSB.print("Status: ");
    SerialUSB.println(status);
    while(1) {}
  }
  SerialUSB.println("ax,ay,az,gx,gy,gz,temp_C");
}

void loop() {
  // read the sensor
  IMU.getAGT();
  // display the data
  SerialUSB.print(IMU.accX(),6);
  SerialUSB.print("\t");
  SerialUSB.print(IMU.accY(),6);
  SerialUSB.print("\t");
  SerialUSB.print(IMU.accZ(),6);
  SerialUSB.print("\t");
  SerialUSB.print(IMU.gyrX(),6);
  SerialUSB.print("\t");
  SerialUSB.print(IMU.gyrY(),6);
  SerialUSB.print("\t");
  SerialUSB.print(IMU.gyrZ(),6);
  SerialUSB.print("\t");
  SerialUSB.println(IMU.temp(),6);
  delay(100);
}