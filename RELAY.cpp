

const int relayPin = 7; // Pin connected to Relay IN

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
}

void loop() {
  delay(10800000); // Wait 3 hours before activating (10,800,000 milliseconds)

  digitalWrite(relayPin, HIGH); // Turn relay ON
  delay(120000);                // Stay ON for 2 minutes to burn wire
  digitalWrite(relayPin, LOW);  // Turn relay OFF

  // Stop after cutting
  while (true) {
  }
}


//termination (daphne)

float temperature, pressure, altitude;
readBMP180Data(temperature, pressure, altitude);
String barometerLog = String("Temp: ") + temperature + "C, Pressure: " + pressure + "hPa, Altitude: " + altitude + "m";
logToSDCard(barometerLog); 

void loop() { 

  if (int(barometerLog[2]) > 10) {              // hPa at 30km IF LIST
    digitalWrite(relayPin, HIGH);
    Serial.println("Relay ON");             // Turn relay ON
    delay(120000);                           // Stay ON for 2 minutes to burn wire
                  // Use Serial.println, not print()
} else {
    digitalWrite(relayPin, LOW); 
    Serial.println("Relay OFF");             // Turn relay OFF
}
// Stop after cutting
while (true) {
  // Infinite loop to stop the program
}
