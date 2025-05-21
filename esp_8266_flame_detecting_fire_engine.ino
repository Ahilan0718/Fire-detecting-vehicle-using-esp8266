#define BLYNK_TEMPLATE_ID "TMPL3RRkLLLJM"
#define BLYNK_DEVICE_NAME "ESP 8266 FLAME DETECTING FIRE ENGINE"
#define BLYNK_AUTH_TOKEN "g1rMRWLnCcBTpv8mTFdOJj-nU5J9MyDt"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Wi-Fi credentials
char ssid[] = "Durai";
char pass[] = "12345678";

// Blynk virtual pins
#define VIRTUAL_PIN_V1 V1  // Button to control motor
#define VIRTUAL_PIN_V2 V2  // Display flame sensor value

// Pin Definitions
#define FLAME_SENSOR_PIN A0 // ESP8266 has only one analog pin (A0)
#define RELAY_PIN D1        // Change to the pin connected to the relay

// Flame sensor threshold (adjust as necessary)
#define FLAME_THRESHOLD 50

void setup() {
  // Start Serial Monitor
  Serial.begin(115200);

  // Initialize Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Initialize Pins
  pinMode(FLAME_SENSOR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Motor off initially

  Serial.println("System Initialized.");
}

// Blynk function to control motor via app
BLYNK_WRITE(VIRTUAL_PIN_V1) {
  int motorState = param.asInt(); // Get value from the Blynk app button
  digitalWrite(RELAY_PIN, motorState);
  Serial.println(motorState ? "Motor ON (via Blynk)" : "Motor OFF (via Blynk)");
}

void loop() {
  // Run Blynk
  Blynk.run();

  // Read Flame Sensor Value
  int flameValue = analogRead(FLAME_SENSOR_PIN); // Read from A0
  Serial.print("Flame Sensor Value: ");
  Serial.println(flameValue);

  // Send Flame Sensor Value to Blynk App
  Blynk.virtualWrite(VIRTUAL_PIN_V2, flameValue);

  // Optionally, notify if flame is detected
  if (flameValue > FLAME_THRESHOLD) {
    Serial.println("Flame detected!");
    Blynk.notify("Warning: Flame detected!");
  }

  delay(1000); // Adjust delay for flame detection rate
}
