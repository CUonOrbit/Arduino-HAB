#include <Wire.h>
#include <Adafruit_AHTX0.h>  // Make sure this library is installed

Adafruit_AHTX0 aht;  // Create the sensor object

void setup() {
  Serial.begin(9600);
  Serial.println("AHT10 Temperature and Humidity Sensor Test");

  if (!aht.begin()) {
    Serial.println("Could not find AHT10 sensor! Check wiring.");
    while (1) delay(10);  // Stop here if sensor not found
  }
  Serial.println("AHT10 sensor found successfully!");
}

void loop() {
  
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);  // Read the sensor

  if (isnan(temp.temperature) || isnan(humidity.relative_humidity)) {
    Serial.println("Error: Sensor reading failed!");
  } else {

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity.relative_humidity);
  Serial.println(" %");

  Serial.println("--------------------");
  delay(1000);  // Wait 1 second between readings
  }}
