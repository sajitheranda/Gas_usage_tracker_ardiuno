#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <HX711.h>

// Load cell setup
HX711 scale;
#define CALIBRATION_FACTOR -7050.0   // Calibration factor for load cell
#define LOADCELL_DOUT_PIN D6         // Data output pin
#define LOADCELL_SCK_PIN D7          // Serial clock pin

// Wi-Fi credentials 
const char* ssid = "wifi";
const char* pass = "password";

// Firebase configuration
FirebaseData firebaseData;
const char* firebaseHost = "https://gas-project-1-default-rtdb.asia-southeast1.firebasedatabase.app/";
const char* firebaseAuth = "dF64y4Z54S3RCgFJNUQmwjMiYxicAF7mMDM9R8SZ";

// NTP server setup for time synchronization
const char* ntpServer = "lk.pool.ntp.org";
const long timeOffset = 0; // GMT offset for Sri Lanka Standard Time

// Network time client
WiFiUDP udp;
NTPClient timeClient(udp, ntpServer, timeOffset);

// Sensor and alarm values
float sensorValue = 26.0;
int alarmValue = 0;
int updateCounter = 0;

void setup() {
  // Initialize GPIO pins
  pinMode(D0, OUTPUT);               // Alarm output pin
  pinMode(LED_BUILTIN, OUTPUT);       // Built-in LED as indicator

  // Connect to Wi-Fi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  // Initialize Firebase and time client
  Firebase.begin(firebaseHost, firebaseAuth);
  timeClient.begin();

  // Initialize and calibrate load cell
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(CALIBRATION_FACTOR);
  scale.tare();                      // Set initial weight to zero
}

void loop() {
  // Update time and read sensor value
  timeClient.update();
  sensorValue = round(scale.get_units() * -0.1 * 100) / 100.0;
  unsigned long epochTime = timeClient.getEpochTime();

  // Construct JSON data for Firebase
  FirebaseJson json;
  json.set("time", epochTime);
  json.set("value", sensorValue);

  // Push data to Firebase at regular intervals
  updateCounter++;
  if (updateCounter == 100) {
    Firebase.pushJSON(firebaseData, "gasapp/gastime", json);
    updateCounter = 0;
  }

  // Update current gas weight in Firebase
  Firebase.setInt(firebaseData, "gasapp/gas", sensorValue);

  // Retrieve alarm status from Firebase and control alarm accordingly
  Firebase.get(firebaseData, "gasapp/alarm");
  alarmValue = firebaseData.intData();

  if (alarmValue == 1) {
    digitalWrite(LED_BUILTIN, LOW);  // Turn on indicator LED
    digitalWrite(D0, HIGH);          // Trigger alarm
  } else {
    digitalWrite(LED_BUILTIN, HIGH); // Turn off indicator LED
    digitalWrite(D0, LOW);           // Deactivate alarm
  }

  // Delay to avoid constant Firebase requests
  delay(60000);
}
