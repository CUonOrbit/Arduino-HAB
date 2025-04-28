#include "BMP180Module.h"

Adafruit_BMP085_Unified bmp;

bool initBMP180() {
    if (!bmp.begin()) {
        Serial.println(F("Couldn't find the sensor"));
        return false;
    }
    Serial.println(F("BMP180 sensor initialized."));
    return true;
}

bool readBMP180Data(float &temperature, float &pressure, float &altitude) {
    sensors_event_t event;
    bmp.getEvent(&event);

    if (event.pressure) {
        pressure = event.pressure;
        
        bmp.getTemperature(&temperature);  
        
        altitude = bmp.pressureToAltitude(1013.25, pressure);  
        return true;
    } else {
        Serial.println(F("Error reading pressure data"));
        return false;
    }
}
