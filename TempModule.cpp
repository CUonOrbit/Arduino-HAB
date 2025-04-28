#include "TempModule.h"

Adafruit_AHTX0 aht;

bool initAHT10() {
  
  if (!aht.begin()) {
    return false;
  }
  return true;
}
bool readAHT10Data(float &temperature, float &humidity) {
    sensors_event_t humEvent, tempEvent;
    aht.getEvent(&humEvent, &tempEvent);

    if (isnan(tempEvent.temperature) || isnan(humEvent.relative_humidity)) {
        return false;
      }

    temperature = tempEvent.temperature;
    humidity    = humEvent.relative_humidity;
    return true;
}