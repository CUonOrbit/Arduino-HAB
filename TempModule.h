#ifndef TEMPMODULE_H
#define TEMPMODULE_H

#include <Wire.h>
#include <Adafruit_AHTX0.h>  

extern Adafruit_AHTX0 aht;

bool initAHT10();

bool readAHT10Data(float &temperature, float &humidity);

#endif