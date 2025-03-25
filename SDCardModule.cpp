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

void logToSDCard(const String &data) {
    // Get the current time in milliseconds (or use an RTC for more accurate time)
    unsigned long currentTime = millis();  // Use RTC time if available

    // Format current time in seconds, minutes, and hours (for simplicity)
    unsigned long hours = (currentTime / 3600000) % 24;
    unsigned long minutes = (currentTime / 60000) % 60;
    unsigned long seconds = (currentTime / 1000) % 60;

    // Create a timestamp string
    String timestamp = String(hours) + ":" + String(minutes) + ":" + String(seconds);

    myFile = SD.open("log.txt", FILE_WRITE);

    // if the file opened okay, write to it:
    if (myFile) {
      // Write timestamp and data to the file
        myFile.print(timestamp);  // Write time first
        myFile.print(" -> ");      // Separator
        myFile.println(data);     // Write the provided data
        myFile.close();           // Close the file

        // Print confirmation to Serial Monitor
        Serial.print("Logged to SD card: ");
        Serial.println(timestamp + " -> " + data);
    } else {
      // if the file didn't open, print an error:
      Serial.println("error opening log.txt");
    }
}

void logErrorToSDCard(const String &message) {
    // Get the current time in milliseconds (or use an RTC for more accurate time)
    unsigned long currentTime = millis();  // Use RTC time if available

    // Format current time in seconds, minutes, and hours (for simplicity)
    unsigned long hours = (currentTime / 3600000) % 24;
    unsigned long minutes = (currentTime / 60000) % 60;
    unsigned long seconds = (currentTime / 1000) % 60;

    // Create a timestamp string
    String timestamp = String(hours) + ":" + String(minutes) + ":" + String(seconds);

    myFile = SD.open("log.txt", FILE_WRITE);

    // if the file opened okay, write to it:
    if (myFile) {
      // Write timestamp and data to the file
        myFile.print("**ERROR** ");  // Write time first
        myFile.print(timestamp);  // Write time first
        myFile.print(" -> ");      // Separator
        myFile.println(message);     // Write the provided data
        myFile.close();           // Close the file

        // Print confirmation to Serial Monitor
        Serial.print("Logged to SD card: ");
        Serial.println(timestamp + " -> " + message);
    } else {
      // if the file didn't open, print an error:
      Serial.println("error opening log.txt");
    }
}
