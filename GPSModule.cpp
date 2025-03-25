#include "GPSModule.h"
#include <Arduino.h>

TinyGPSPlus gps; // Define gps object here

bool readGPSData(TinyGPSPlus &gps)
{
  while (Serial1.available() > 0)
  {
    char c = Serial1.read();
    if (gps.encode(c) && gps.location.isUpdated())
    {
      return true;
    }
  }
  return false;
}

void displayGPSInfo(TinyGPSPlus &gps)
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(", "));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}

bool hasGPSFix()
{
  return gps.location.isValid() &&
         gps.date.isValid() &&
         gps.time.isValid();
}
