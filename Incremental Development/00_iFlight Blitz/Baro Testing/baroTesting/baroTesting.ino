#include <SPI.h>
#include <Arduino.h>
#include <Wire.h>
#include "BlitzH743.h"       // Provides I2C2_SDA_PIN, I2C2_SCL_PIN, Serial, etc.
#include <Adafruit_DPS310.h>
#include <Adafruit_Sensor.h>         // For sensors_event_t

#define DPS310_ADDR 0x76  // Sensor address as detected from your I2C scan

// Create a TwoWire instance for I2C2 using board-defined pins
TwoWire myI2C2(PIN_I2C2_SDA, PIN_I2C2_SCL);

// Create an instance of the DPS310 sensor
Adafruit_DPS310 dps;

void setup() {
  // Initialize USB serial communication
  Serial.begin(115200);
  uint32_t startTime = millis();
  while (!Serial && millis() - startTime < 3000) {
    delay(10);
  }
  Serial.println("DPS310 test starting...");

  // Begin I2C on our custom bus (I2C2)
  myI2C2.begin();

  // Initialize the DPS310 sensor in I2C mode:
  // The begin_I2C() function requires the sensor address and a pointer to our TwoWire instance.
  if (!dps.begin_I2C(DPS310_ADDR, &myI2C2)) {
    Serial.println("Could not find a valid DPS310 sensor, check wiring!");
    while (1) { delay(10); }
  }
  Serial.println("DPS310 sensor found!");
}

void loop() {
  // Create event structures for pressure and temperature.
  sensors_event_t pressure_event, temp_event;

  // Use the unified sensor API to get sensor readings.
  // getEvents() returns true if the sensor data was successfully updated.
  if (!dps.getEvents(&pressure_event, &temp_event)) {
    Serial.println("Sensor read error");
  } else {
    Serial.print("Pressure: ");
    Serial.print(pressure_event.pressure);
    Serial.print(" Pa, Temperature: ");
    Serial.print(temp_event.temperature);
    Serial.println(" C");
  }

  delay(100);
}
