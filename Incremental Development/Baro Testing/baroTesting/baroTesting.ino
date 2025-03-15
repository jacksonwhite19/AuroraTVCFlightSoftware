#include <SPI.h>
#include <Arduino.h>
#include <Wire.h>
#include "MatekH743_Pinout.h"       // Provides I2C2_SDA_PIN, I2C2_SCL_PIN, SerialUSB, etc.
#include <Adafruit_DPS310.h>
#include <Adafruit_Sensor.h>         // For sensors_event_t

#define DPS310_ADDR 0x76  // Sensor address as detected from your I2C scan

// Create a TwoWire instance for I2C2 using board-defined pins
TwoWire myI2C2(I2C2_SDA_PIN, I2C2_SCL_PIN);

// Create an instance of the DPS310 sensor
Adafruit_DPS310 dps;

void setup() {
  // Initialize USB serial communication
  SerialUSB.begin(115200);
  uint32_t startTime = millis();
  while (!SerialUSB && millis() - startTime < 3000) {
    delay(10);
  }
  SerialUSB.println("DPS310 test starting...");

  // Begin I2C on our custom bus (I2C2)
  myI2C2.begin();

  // Initialize the DPS310 sensor in I2C mode:
  // The begin_I2C() function requires the sensor address and a pointer to our TwoWire instance.
  if (!dps.begin_I2C(DPS310_ADDR, &myI2C2)) {
    SerialUSB.println("Could not find a valid DPS310 sensor, check wiring!");
    while (1) { delay(10); }
  }
  SerialUSB.println("DPS310 sensor found!");
}

void loop() {
  // Create event structures for pressure and temperature.
  sensors_event_t pressure_event, temp_event;

  // Use the unified sensor API to get sensor readings.
  // getEvents() returns true if the sensor data was successfully updated.
  if (!dps.getEvents(&pressure_event, &temp_event)) {
    SerialUSB.println("Sensor read error");
  } else {
    SerialUSB.print("Pressure: ");
    SerialUSB.print(pressure_event.pressure);
    SerialUSB.print(" Pa, Temperature: ");
    SerialUSB.print(temp_event.temperature);
    SerialUSB.println(" C");
  }

  delay(100);
}
