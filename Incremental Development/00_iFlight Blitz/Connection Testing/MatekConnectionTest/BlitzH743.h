#pragma once

// Board Identity
#define TARGET_BOARD_IDENTIFIER "BLZH"
#define USE_FLASHFS
#define USE_SDCARD
#define SDCARD_SDIO

// Gyro (ICM42688P on SPI1)
#define USE_GYRO
#define GYRO_1_SPI_INSTANCE SPI1
#define GYRO_1_CS_PIN PC15
#define GYRO_1_EXTI_PIN PB2
#define USE_ICM42688P

// Barometer (DPS310 on I2C4)
#define USE_BARO
#define USE_DPS310
#define BARO_I2C_INSTANCE I2C4
#define BARO_I2C_SCL_PIN PB10
#define BARO_I2C_SDA_PIN PB11

// OSD (MAX7456 on SPI3)
#define USE_OSD
#define USE_MAX7456
#define OSD_SPI_INSTANCE SPI3
#define OSD_CS_PIN PB12

// Motors
#define MOTOR1_PIN PB0
#define MOTOR2_PIN PB1
#define MOTOR3_PIN PA0
#define MOTOR4_PIN PA1
#define MOTOR5_PIN PA2
#define MOTOR6_PIN PA3
#define MOTOR7_PIN PD12
#define MOTOR8_PIN PD13

// Servos
#define SERVO1_PIN PD14
#define SERVO2_PIN PD15
#define SERVO3_PIN PE5
#define SERVO4_PIN PE6

// Beeper
#define BEEPER_PIN PA15

// LEDs
#define LED_STRIP_PIN PA8
#define LED1_PIN PE3
#define LED2_PIN PE4

// UARTs
#define UART1_TX_PIN PA9
#define UART1_RX_PIN PA10
#define UART2_TX_PIN PD5
#define UART2_RX_PIN PD6
#define UART3_TX_PIN PD8
#define UART3_RX_PIN PD9
#define UART4_TX_PIN PB9
#define UART4_RX_PIN PB8
#define UART6_TX_PIN PC6
#define UART6_RX_PIN PC7
#define UART7_TX_PIN PE8
#define UART7_RX_PIN PE7
#define UART8_TX_PIN PE1
#define UART8_RX_PIN PE0

// I2C (Other sensors and peripherals)
#define I2C1_SCL_PIN PB6  // Airspeed MS4525
#define I2C1_SDA_PIN PB7
#define I2C4_SCL_PIN PB10 // Barometer DPS310
#define I2C4_SDA_PIN PB11

// SPI (besides gyro/osd)
#define SPI1_SCK_PIN  PA5
#define SPI1_MISO_PIN PA6
#define SPI1_MOSI_PIN PD7

#define SPI3_SCK_PIN  PB3
#define SPI3_MISO_PIN PB4
#define SPI3_MOSI_PIN PB5

// SDIO (SD card)
#define SDIO_CLK_PIN PC12
#define SDIO_CMD_PIN PD2
#define SDIO_D0_PIN  PC8
#define SDIO_D1_PIN  PC9
#define SDIO_D2_PIN  PC10
#define SDIO_D3_PIN  PC11

// ADC (Battery & Current Monitoring)
#define ADC_BATT_PIN PC0
#define ADC_CURR_PIN PC1
#define ADC_RSSI_PIN PC5
#define ADC_EXT_PIN  PC4

// PinIO
#define PINIO1_PIN PD10
#define PINIO2_PIN PD11

// Optional Features
#define USE_MAG       // External compass on I2C
#define USE_GPS       // Via UART4 or UART6
