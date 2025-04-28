#include <Wire.h>
#include <WDT.h> 
#include "GPSModule.h"
#include "SDCardModule.h"
#include "BMP180Module.h"
#include "TempModule.h" 
#include "Arduino_LED_Matrix.h" // Include the LED Matrix library
#include "config.h"

ArduinoLEDMatrix matrix; // Create an LED matrix object

const long wdtInterval = 5000;  // 5 seconds timeout
unsigned long wdtMillis = 0;

// LED blink timing
const int errorBlinkInterval = 500; // milliseconds
bool errorLedState = false;
unsigned long lastBlinkTime = 0;

bool isTerminating = false;
unsigned long terminationStart = 0;

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
  matrix.begin(); 

  Serial.begin(115200);
  while (!Serial);

  delay(1000);
  Serial.println(F("NEO-6M GPS + SD Logging"));
  Serial.print(F("TinyGPSPlus v")); Serial.println(TinyGPSPlus::libraryVersion());

  // Track module initialization status
  bool sdOK = initSDCard(SD_CS_PIN);
  bool bmpOK = initBMP180();
  bool tempOK = initAHT10();

  if (!sdOK) Serial.println(F("SD card initialization failed."));
  if (!bmpOK) Serial.println(F("BMP180 initialization failed."));


  Serial.print("SD Card status: ");
  Serial.println(sdOK ? "Success" : "Failed");

  Serial.print("BMP180 status: ");
  Serial.println(bmpOK ? "Success" : "Failed");

  Serial.print("AHT10 init: ");
  Serial.println(tempOK ? "Success" : "FAILED");

  
  if (!sdOK || !bmpOK|| !tempOK) {
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

  // GPS data
  if (readGPSData(gps)) {
    String gpsLog = String("Lat: ") + gps.location.lat() +
                    ",Lng: " + gps.location.lng() +
                    ",Date: " + gps.date.month() + "/" + gps.date.day() + "/" + gps.date.year() +
                    ",Time: " + gps.time.hour() + ":" + gps.time.minute() + ":" + gps.time.second();
    logToSDCard(gpsLog);  
  } else {
    logToSDCard("Error: GPS reading failed!");
  }

  // BMP data
  float temperature, pressure, altitude;
  if(readBMP180Data(temperature, pressure, altitude)){
    String barometerLog = String("Temp: ") + temperature + "C, Pressure: " + pressure + "hPa, Altitude: " + altitude + "m";
    logToSDCard(barometerLog);  
  } else {
    logToSDCard("Error: BMP180 reading failed!");
  }
  
   // Temp and humidity data
  float tC, hPct;
  if (readAHT10Data(tC, hPct)) {
    String tempLog = String("Temp: ") + tC + "C, Humidity: " + hPct + "%";
    logToSDCard(tempLog);
  } else {
    logToSDCard("Error: AHT10 reading failed!");
  }

  // Termination
  unsigned long currentTime = millis();  
  if(terminationStart == 0 && ((currentTime > TERMINATION_TIME  && !terminationStart) || altitude > TERMINATION_HEIGHT)) {
    logToSDCard("TERMINATING FLIGHT"); 
    digitalWrite(RELAY_PIN, HIGH); // Turn relay ON
    isTerminating = true;
    terminationStart = currentTime;
  }
  else if(terminationStart && currentTime - terminationStart > TERMINATION_CUT_TIME){
    logToSDCard("FLIGHT TERMINATION COMPLETE"); 
    digitalWrite(RELAY_PIN, LOW);  // Turn relay OFF
    isTerminating = false;
  }
  
  delay(2000);
}