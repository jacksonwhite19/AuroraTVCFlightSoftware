#pragma once

// Beeper
#define BEEPER_PIN PA15

// Motors
#define MOTOR1 PB0
#define MOTOR2 PB1
#define MOTOR3 PA0
#define MOTOR4 PA1
#define MOTOR5 PA2
#define MOTOR6 PA3
#define MOTOR7 PD12
#define MOTOR8 PD13

// Servos
#define SERVO1 PE5
#define SERVO2 PE6

// LED
#define LED1_PIN PE3
#define LED2_PIN PE4
#define LED_STRIP_PIN PA8

// UART
#define UART1_TX PA9
#define UART1_RX PA10
#define UART2_TX PD5
#define UART2_RX PD6
#define UART3_TX PD8
#define UART3_RX PD9
#define UART4_TX PB9
#define UART4_RX PB8
#define UART6_TX PC6
#define UART6_RX PC7
#define UART7_TX PE8
#define UART7_RX PE7
#define UART8_TX PE1
#define UART8_RX PE0

// I2C
#define I2C1_SCL PB6
#define I2C1_SDA PB7
#define I2C2_SCL PB10
#define I2C2_SDA PB11

// SPI
#define SPI1_SCK PA5
#define SPI1_MISO PA6
#define SPI1_MOSI PD7
#define SPI2_SCK PB13
#define SPI2_MISO PB14
#define SPI2_MOSI PB15
#define SPI3_SCK PB3
#define SPI3_MISO PB4
#define SPI3_MOSI PB5
#define SPI4_SCK PE12
#define SPI4_MISO PE13
#define SPI4_MOSI PE14

// ADC
#define ADC_BATT PC0
#define ADC_CURR PC1
#define ADC_RSSI PC5
#define ADC_EXT PC4

// SDIO (for SD card)
#define SDIO_CK PC12
#define SDIO_CMD PD2
#define SDIO_D0 PC8
#define SDIO_D1 PC9
#define SDIO_D2 PC10
#define SDIO_D3 PC11

// Pin I/O
#define PINIO1 PD10
#define PINIO2 PD11

// OSD
#define OSD_CS PB12

// Gyro and IMU
#define GYRO_EXTI1 PB2
#define GYRO_EXTI2 PE15
#define GYRO_CS1 PC15
#define GYRO_CS2 PE11

// SPI3 chip select pads
#define SPI3_CS1 PD4
#define SPI3_CS2 PE2

// PPM and other signals
#define PPM_PIN PC7
