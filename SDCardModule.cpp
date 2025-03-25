#include "SDCardModule.h"

File myFile;

bool initSDCard(uint8_t csPin) {
    if (!SD.begin(csPin)) {
        Serial.println(F("SD card initialization failed!"));
        return false;
    }
    Serial.println(F("SD card initialized."));
    return true;
}

String getTimestamp(){
    unsigned long currentTime = millis();  

    unsigned long hours = (currentTime / 3600000) % 24;
    unsigned long minutes = (currentTime / 60000) % 60;
    unsigned long seconds = (currentTime / 1000) % 60;

    String timestamp = String(hours) + ":" + String(minutes) + ":" + String(seconds);

    return timestamp;
}

void logToSDCard(const String &data) {

    String timestamp = getTimestamp();
    myFile = SD.open("log.txt", FILE_WRITE);

    if (myFile) {
        myFile.print(timestamp);  
        myFile.print(" -> ");     
        myFile.println(data);  
        myFile.close();        

        Serial.print("Logged to SD card: ");
        Serial.println(timestamp + " -> " + data);
    } else {
      Serial.println("error opening log.txt");
    }
}

void logErrorToSDCard(const String &message) {

    String timestamp = getTimestamp();
    myFile = SD.open("log.txt", FILE_WRITE);

    if (myFile) {
        myFile.print("**ERROR** ");  
        myFile.print(timestamp);  
        myFile.print(" -> ");      
        myFile.println(message);     
        myFile.close();          

        Serial.print("Logged to SD card: ");
        Serial.println(timestamp + " -> " + message);
    } else {
      Serial.println("error opening log.txt");
    }
}
