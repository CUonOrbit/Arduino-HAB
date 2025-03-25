#include "BMP180Module.h"

// Define bmp object here (only once in the source file)
Adafruit_BMP085_Unified bmp;

bool initBMP180() {
    if (!bmp.begin()) {
        Serial.println(F("Couldn't find the sensor"));
        return false;
    }
    Serial.println(F("BMP180 sensor initialized."));
    return true;
}

void readBMP180Data(float &temperature, float &pressure, float &altitude) {
    sensors_event_t event;
    bmp.getEvent(&event);

    if (event.pressure) {
        pressure = event.pressure;
        
        // Declare a float variable to hold the temperature value
        bmp.getTemperature(&temperature);  // Correctly pass a pointer to store temperature
        
        altitude = bmp.pressureToAltitude(1013.25, pressure);  // Altitude at sea level pressure
    } else {
        Serial.println(F("Error reading pressure data"));
    }
}
