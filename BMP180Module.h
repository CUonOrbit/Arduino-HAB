#ifndef BMP180MODULE_H
#define BMP180MODULE_H

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

// Declare bmp as an external object to avoid multiple definitions
extern Adafruit_BMP085_Unified bmp;

bool initBMP180();
void readBMP180Data(float &temperature, float &pressure, float &altitude);

#endif
