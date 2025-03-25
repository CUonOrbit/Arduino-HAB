// config.h - Pin Definitions and Hardware Settings

#pragma once

// GPS Module (NEO-6M)
#define GPS_RX_PIN        0            // SoftwareSerial RX (if used)
#define GPS_TX_PIN        1            // SoftwareSerial TX

// BMP180 (I2C Pins - fixed on Uno)
#define BMP180_SDA_PIN    A4           // I2C SDA
#define BMP180_SCL_PIN    A5           // I2C SCL

// SD Card Module (SPI Pins - fixed on Uno)
#define SD_CS_PIN         4           // Chip Select
// (MOSI=11, MISO=12, SCK=13 are fixed in SPI)
