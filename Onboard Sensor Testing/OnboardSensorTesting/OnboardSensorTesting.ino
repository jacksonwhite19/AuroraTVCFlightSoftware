#include <SPI.h>
#include "MatekH743_Pinout.h"  // Provides board-specific definitions (e.g. GYRO_1_CS_PIN)
#include <ICM42688.h>          // ICM42688 Arduino library

// Instantiate the sensor using the SPI constructor with the CS pin from the board file.
ICM42688 IMU(SPI, GYRO_1_CS_PIN);

//////////////////////////////////////////////////////
// Helper function: Manual low-level SPI register read
uint8_t manualReadRegister(uint8_t csPin, uint8_t reg) {
  uint8_t value;
  digitalWrite(csPin, LOW);
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
  SPI.transfer(reg | 0x80);  // Set read flag (MSB high)
  value = SPI.transfer(0x00); // Dummy byte to clock out data
  SPI.endTransaction();
  digitalWrite(csPin, HIGH);
  return value;
}

//////////////////////////////////////////////////////
// Helper function: Manual Betaflight-style sensor initialization
void manualBetaflightInit(uint8_t csPin) {
  // Soft reset: Write 0x80 to PWR_MGMT0 (register 0x4E)
  digitalWrite(csPin, LOW);
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
  SPI.transfer(0x4E);    // PWR_MGMT0 register
  SPI.transfer(0x80);    // Soft reset command
  SPI.endTransaction();
  digitalWrite(csPin, HIGH);
  delay(100);            // Wait 100 ms for reset

  // Wake up sensor: Write 0x01 to PWR_MGMT0 (select internal oscillator)
  digitalWrite(csPin, LOW);
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
  SPI.transfer(0x4E);
  SPI.transfer(0x01);
  SPI.endTransaction();
  digitalWrite(csPin, HIGH);
  delay(50);             // Wait 50 ms for wake-up

  // Configure gyroscope: Write 0x03 to GYRO_CONFIG0 (register 0x4F) for full-scale range (example value)
  digitalWrite(csPin, LOW);
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
  SPI.transfer(0x4F);
  SPI.transfer(0x03);
  SPI.endTransaction();
  digitalWrite(csPin, HIGH);

  // Configure accelerometer: Write 0x03 to ACCEL_CONFIG0 (register 0x50) for full-scale range (example value)
  digitalWrite(csPin, LOW);
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
  SPI.transfer(0x50);
  SPI.transfer(0x03);
  SPI.endTransaction();
  digitalWrite(csPin, HIGH);

  // Read WHO_AM_I (register 0x75) for debugging:
  uint8_t who = manualReadRegister(csPin, 0x75);
  SerialUSB.print("Manual WHO_AM_I: 0x");
  SerialUSB.println(who, HEX);
}

//////////////////////////////////////////////////////
void setup() {
  // Initialize USB Serial communication using SerialUSB (per your MatekConnectionTest configuration)
  SerialUSB.begin(115200);
  while (!SerialUSB) {
    ; // Wait until SerialUSB is ready.
  }
  
  // Initialize SPI bus
  SPI.begin();
  
  // Set the CS pin as OUTPUT and default HIGH.
  pinMode(GYRO_1_CS_PIN, OUTPUT);
  digitalWrite(GYRO_1_CS_PIN, HIGH);

  SerialUSB.println("Starting manual Betaflight-style initialization...");
  manualBetaflightInit(GYRO_1_CS_PIN);
  
  // Now, call the library's begin() to perform its initialization.
  // The library's begin() may perform additional checks and configuration.
  int status = IMU.begin();
  if (status < 0) {
    SerialUSB.println("IMU initialization unsuccessful");
    SerialUSB.println("Check wiring or try cycling power");
    SerialUSB.print("Status: ");
    SerialUSB.println(status);
    while (1) { } // Halt execution if initialization fails.
  }
  SerialUSB.println("IMU initialized successfully.");
  SerialUSB.println("ax,ay,az,gx,gy,gz,temp_C");
}

//////////////////////////////////////////////////////
void loop() {
  // Update sensor data using the library's method (getAGT() as per the provided example)
  IMU.getAGT();

  // Print sensor data with 6-digit precision.
  SerialUSB.print(IMU.accX(), 6);
  SerialUSB.print("\t");
  SerialUSB.print(IMU.accY(), 6);
  SerialUSB.print("\t");
  SerialUSB.print(IMU.accZ(), 6);
  SerialUSB.print("\t");
  SerialUSB.print(IMU.gyrX(), 6);
  SerialUSB.print("\t");
  SerialUSB.print(IMU.gyrY(), 6);
  SerialUSB.print("\t");
  SerialUSB.print(IMU.gyrZ(), 6);
  SerialUSB.print("\t");
  SerialUSB.println(IMU.temp(), 6);
  
  delay(100);
}
