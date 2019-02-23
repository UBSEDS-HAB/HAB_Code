#ifndef __CONFIG_H__
#define __CONFIG_H__

// Error LED
#define LED_PIN 7

// Buzzer rings below the defined altitude, BUZZ_CUTOFF (meters)
// Passive buzzer is used, and BUZZER_FREQ tone is sent on BUZZER_PIN
#define BUZZER_PIN 9
#define BUZZER_CUTOFF 1000.0
#define BUZZER_FREQ 1000

// BAUD RATE for serial
#define BAUD_RATE 9600

// Pressure at sea level according to weather forcast
// Used for altitude approximation
#define SEA_LEVEL_PRESSURE 1027.0

// Data pin for SD Card
// CLK 13
// SDO 12
// DI 11
#define CS_SD 10

// BMP PINS
// SDI to SDA
// SCK TO SCL

// Voltage divider resister values (R1 and R2) and analogue
// input pin to be read from
#define R1 1000
#define R2 1000000
#define voltagePin A1

#endif