// config.h - Pin Definitions and Hardware Settings

#pragma once

// GPS Module (NEO-6M)
#define GPS_RX_PIN        0            
#define GPS_TX_PIN        1            

// I2C Pins - fixed on Uno
#define SDA_PIN    A4           
#define SCL_PIN    A5         

// SD Card Module (SPI Pins - fixed on Uno)
#define SD_CS_PIN         4           
// (MOSI=11, MISO=12, SCK=13 are fixed in SPI)

#define RELAY_PIN         7
#define TERMINATION_HEIGHT   30000  // In metres
#define TERMINATION_TIME     10800000  // In milliseconds
#define TERMINATION_CUT_TIME 120000