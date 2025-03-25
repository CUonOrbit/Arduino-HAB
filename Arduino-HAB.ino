#include <Wire.h>
#include <WDT.h> 
#include "GPSModule.h"
#include "SDCardModule.h"
#include "BMP180Module.h"
#include "Arduino_LED_Matrix.h" // Include the LED Matrix library
#include "config.h"

ArduinoLEDMatrix matrix; // Create an LED matrix object

const long wdtInterval = 5000;  // 5 seconds timeout
unsigned long wdtMillis = 0;

// LED blink timing
const int errorBlinkInterval = 500; // milliseconds
bool errorLedState = false;
unsigned long lastBlinkTime = 0;

uint8_t smallCircle[8][12] = {
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,1,1,1,1,0,0,0,0,0},
  {0,0,1,0,0,0,0,1,0,0,0,0},
  {0,1,0,0,0,0,0,0,1,0,0,0},
  {0,1,0,0,0,0,0,0,1,0,0,0},
  {0,0,1,0,0,0,0,1,0,0,0,0},
  {0,0,0,1,1,1,1,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0}
};

uint8_t xPattern[8][12] = {
  {1,0,0,0,0,0,0,0,0,0,0,1},
  {0,1,0,0,0,0,0,0,0,0,1,0},
  {0,0,1,0,0,0,0,0,0,1,0,0},
  {0,0,0,1,0,0,0,0,1,0,0,0},
  {0,0,0,0,1,0,0,1,0,0,0,0},
  {0,0,0,0,0,1,1,0,0,0,0,0},
  {0,0,0,0,0,1,1,0,0,0,0,0},
  {0,0,0,0,1,0,0,1,0,0,0,0}
};

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  matrix.begin(); // Initialize the LED matrix

  Serial.begin(115200);
  while (!Serial);

  delay(1000);
  Serial.println(F("NEO-6M GPS + SD Logging"));
  Serial.print(F("TinyGPSPlus v")); Serial.println(TinyGPSPlus::libraryVersion());

  // Track module initialization status
  bool sdOK = initSDCard(SD_CS_PIN);
  bool bmpOK = initBMP180();

  if (!sdOK) Serial.println(F("SD card initialization failed."));
  if (!bmpOK) Serial.println(F("BMP180 initialization failed."));

  Serial.print("SD Card status: ");
  Serial.println(sdOK ? "Success" : "Failed");

  Serial.print("BMP180 status: ");
  Serial.println(bmpOK ? "Success" : "Failed");

  // If either failed, enter blinking loop
  if (!sdOK || !bmpOK) {
    errorLedState = true;
  }

  Serial1.begin(9600); // GPS
}

void loop() {
  // Refresh watchdog (if enabled)
  /*
  if (millis() - wdtMillis >= wdtInterval - 1) {
    WDT.refresh();
    wdtMillis = millis();
  }
  */

  // Error LED handling
  if (errorLedState) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  if(hasGPSFix()){
    matrix.renderBitmap(smallCircle, 8, 12);
  }
  else{
    matrix.renderBitmap(xPattern, 8, 12);
  }
  // Read GPS data
  if (readGPSData(gps)) {
    String gpsLog = String("Lat: ") + gps.location.lat() +
                    ",Lng: " + gps.location.lng() +
                    ",Date: " + gps.date.month() + "/" + gps.date.day() + "/" + gps.date.year() +
                    ",Time: " + gps.time.hour() + ":" + gps.time.minute() + ":" + gps.time.second();
    logToSDCard(gpsLog);  // Log GPS info
  }

  float temperature, pressure, altitude;
  readBMP180Data(temperature, pressure, altitude);
  String barometerLog = String("Temp: ") + temperature + "C, Pressure: " + pressure + "hPa, Altitude: " + altitude + "m";
  logToSDCard(barometerLog);  

    delay(2000);
  
}