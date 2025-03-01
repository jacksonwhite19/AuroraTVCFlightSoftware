#include <SPI.h>
#include "MatkeH743_Pinout.h"

#define CS_PIN PC15  // Set the chip select pin to PC15 for MPU6000

// MPU6000 register addresses
#define MPU6000_PWR_MGMT_1   0x6B
#define MPU6000_ACCEL_XOUT_H 0x3B
#define MPU6000_WHO_AM_I     0x75

void writeRegister(uint8_t reg, uint8_t value) {
    digitalWrite(CS_PIN, LOW);
    SPI.transfer(reg);
    SPI.transfer(value);
    digitalWrite(CS_PIN, HIGH);
}

uint16_t readRegister16(uint8_t reg) {
    digitalWrite(CS_PIN, LOW);
    SPI.transfer(reg | 0x80);
    uint8_t highByte = SPI.transfer(0x00);
    uint8_t lowByte = SPI.transfer(0x00);
    digitalWrite(CS_PIN, HIGH);
    return (highByte << 8) | lowByte;
}

void checkMPU6000() {
    uint16_t whoAmI = readRegister16(MPU6000_WHO_AM_I);
    Serial.print("WHO_AM_I: 0x");
    Serial.println(whoAmI, HEX);

    uint16_t powerMgmt = readRegister16(MPU6000_PWR_MGMT_1);
    Serial.print("Power Management: 0x");
    Serial.println(powerMgmt, HEX);
}

void setup() {
    Serial.begin(115200);
    SPI.begin();
    pinMode(CS_PIN, OUTPUT);
    digitalWrite(CS_PIN, HIGH);

    // Initialize MPU6000
    writeRegister(MPU6000_PWR_MGMT_1, 0x00);
    Serial.println("MPU6000 initialized.");

    // Check MPU6000 connection and power state
    checkMPU6000();
}

void loop() {
    int16_t accelX = readRegister16(MPU6000_ACCEL_XOUT_H);
    int16_t accelY = readRegister16(MPU6000_ACCEL_XOUT_H + 2);
    int16_t accelZ = readRegister16(MPU6000_ACCEL_XOUT_H + 4);

    Serial.print("Accel X: "); Serial.print(accelX);
    Serial.print(" | Accel Y: "); Serial.print(accelY);
    Serial.print(" | Accel Z: "); Serial.println(accelZ);

    delay(500);
}
