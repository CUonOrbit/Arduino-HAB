// config.h - Pin Definitions and Hardware Settings

#pragma once

// GPS Module (NEO-6M)
#define GPS_RX_PIN        0            
#define GPS_TX_PIN        1            

// BMP180 (I2C Pins - fixed on Uno)
#define BMP180_SDA_PIN    A4           
#define BMP180_SCL_PIN    A5         

// SD Card Module (SPI Pins - fixed on Uno)
#define SD_CS_PIN         4           
// (MOSI=11, MISO=12, SCK=13 are fixed in SPI)
