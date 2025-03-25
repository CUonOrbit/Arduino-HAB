#ifndef GPSMODULE_H
#define GPSMODULE_H

#include <TinyGPSPlus.h>

bool readGPSData(TinyGPSPlus &gps);

void displayGPSInfo(TinyGPSPlus &gps);

bool hasGPSFix();

extern TinyGPSPlus gps; 

#endif
