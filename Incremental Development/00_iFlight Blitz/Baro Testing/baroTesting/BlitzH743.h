// BlitzH743.h - Pin definitions for iFlight Blitz H7 Pro (STM32H743xx)
// Extracted from ArduPilot hwdef.dat for use in Arduino-based custom firmware

#ifndef BLITZ_H743_H
#define BLITZ_H743_H

// ============================
// ===== MCU Definitions =====
// ============================
#define MCU_CLOCK_HZ       480000000
#define OSCILLATOR_HZ      8000000

// ============================
// ===== Serial Ports ========
// ============================
#define PIN_SERIAL1_TX     PA9   // USART1 TX (VTX)
#define PIN_SERIAL1_RX     PA10  // USART1 RX

#define PIN_SERIAL2_TX     PD5   // USART2 TX (RC IN)
#define PIN_SERIAL2_RX     PD6   // USART2 RX

#define PIN_SERIAL3_TX     PD8   // USART3 TX
#define PIN_SERIAL3_RX     PD9   // USART3 RX

#define PIN_SERIAL4_TX     PB9   // UART4 TX (GPS)
#define PIN_SERIAL4_RX     PB8   // UART4 RX

#define PIN_SERIAL5_TX     PC6   // USART6 TX (ESC Telemetry)
#define PIN_SERIAL5_RX     PC7   // USART6 RX

#define PIN_SERIAL6_TX     PE8   // UART7 TX
#define PIN_SERIAL6_RX     PE7   // UART7 RX

#define PIN_SERIAL7_TX     PE1   // UART8 TX
#define PIN_SERIAL7_RX     PE0   // UART8 RX

// ============================
// ===== I2C Ports ===========
// ============================
#define PIN_I2C1_SCL       PB6
#define PIN_I2C1_SDA       PB7

#define PIN_I2C2_SCL       PB10
#define PIN_I2C2_SDA       PB11

// ============================
// ===== SPI Devices =========
// ============================
// SPI1 - IMU
#define PIN_SPI1_SCK       PA5
#define PIN_SPI1_MISO      PA6
#define PIN_SPI1_MOSI      PD7
#define PIN_IMU1_CS        PC15

// SPI2 - OSD
#define PIN_SPI2_SCK       PB13
#define PIN_SPI2_MISO      PB14
#define PIN_SPI2_MOSI      PB15
#define PIN_OSD_CS         PB12

// ============================
// ===== Motor Outputs =======
// ============================
#define PIN_MOTOR1         PB0   // TIM3_CH3
#define PIN_MOTOR2         PB1   // TIM3_CH4
#define PIN_MOTOR3         PA0   // TIM5_CH1
#define PIN_MOTOR4         PA1   // TIM5_CH2
#define PIN_MOTOR5         PA2   // TIM5_CH3
#define PIN_MOTOR6         PA3   // TIM5_CH4
#define PIN_MOTOR7         PD12  // TIM4_CH1
#define PIN_MOTOR8         PD13  // TIM4_CH2
#define PIN_MOTOR9         PD14  // TIM4_CH3 (Daughterboard)
#define PIN_MOTOR10        PD15  // TIM4_CH4 (Daughterboard)
#define PIN_MOTOR11        PE5   // TIM15_CH1 (NODMA)
#define PIN_MOTOR12        PE6   // TIM15_CH2 (NODMA)

// ============================
// ===== LEDs ================
// ============================
#define PIN_LED_STATUS     PE3   // LED0
#define PIN_LED_1          PE4   // LED1
#define PIN_LED_PWM        PA8   // TIM1_CH1 (PWM M9)

// ============================
// ===== ADC Pins ============
// ============================
#define PIN_BATT_VOLTAGE   PC0
#define PIN_BATT_CURRENT   PC1
#define PIN_RSSI_INPUT     PC5
#define PIN_AIRSPEED       PC4

// ============================
// ===== CAN Bus =============
// ============================
#define PIN_CAN1_RX        PD0
#define PIN_CAN1_TX        PD1
#define PIN_CAN1_SILENT    PD3

// ============================
// ===== SD Card =============
// ============================
#define PIN_SDMMC_D0       PC8
#define PIN_SDMMC_D1       PC9
#define PIN_SDMMC_D2       PC10
#define PIN_SDMMC_D3       PC11
#define PIN_SDMMC_CK       PC12
#define PIN_SDMMC_CMD      PD2

// ============================
// ===== Other Peripherals ===
// ============================
#define PIN_BUZZER         PA15  // TIM2_CH1
#define PIN_VTX_POWER      PD10
#define PIN_CAM_SWITCH     PD11

#endif // BLITZ_H743_H
