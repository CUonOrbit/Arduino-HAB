

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