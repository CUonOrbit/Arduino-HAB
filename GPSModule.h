#ifndef GPSMODULE_H
#define GPSMODULE_H

#include <TinyGPSPlus.h>

// Reads data from Serial1 and feeds it to TinyGPSPlus parser
bool readGPSData(TinyGPSPlus &gps);

// Displays parsed GPS data to Serial
void displayGPSInfo(TinyGPSPlus &gps);

// Returns true if GPS has a valid location, date, and time
bool hasGPSFix();

extern TinyGPSPlus gps; // Declare gps object globally

#endif
