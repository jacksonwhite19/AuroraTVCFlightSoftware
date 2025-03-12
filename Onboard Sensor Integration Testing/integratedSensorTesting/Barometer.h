#ifndef BAROMETER_H
#define BAROMETER_H
#include <SPI.h>
#include "MatekH743_Pinout.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_DPS310.h>
#include <Adafruit_Sensor.h>

// Define the DPS310 I2C address
#define DPS310_ADDR 0x76

// Create a TwoWire instance for I2C2 using board-defined pins.
TwoWire myI2C2(I2C2_SDA_PIN, I2C2_SCL_PIN);

// Create an instance of the DPS310 sensor.
Adafruit_DPS310 dps;

// Structure to hold barometer data
struct BarometerData {
  float pressure;
  float temperature;
};

// Function to initialize the barometer sensor (adapted from your baroTesting.ino setup)
void initBarometer() {
  myI2C2.begin();

  if (!dps.begin_I2C(DPS310_ADDR, &myI2C2)) {
    SerialUSB.println("Could not find a valid DPS310 sensor, check wiring!");
    while (1) {
      delay(10);
    }
  }
  SerialUSB.println("DPS310 sensor found!");
}

// Function to read data from the barometer sensor (adapted from your baroTesting.ino loop)
BarometerData readBarometer() {
  BarometerData data;
  sensors_event_t pressure_event, temp_event;

  if (!dps.getEvents(&pressure_event, &temp_event)) {
    SerialUSB.println("Sensor read error");
    // Optionally, you could set error values here.
    data.pressure = NAN;
    data.temperature = NAN;
  } else {
    data.pressure = pressure_event.pressure;
    data.temperature = temp_event.temperature;
    data.temperature = (temp_event.temperature / 333.87) + 21.0;
  }
  return data;
}

#endif // BAROMETER_H

