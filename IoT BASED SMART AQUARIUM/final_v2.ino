#include <Arduino.h>
#include <WiFi.h>  //we are using the ESP32
//#include <ESP8266WiFi.h>      // uncomment this line if you are using esp8266 and comment the line above
#include <Firebase_ESP_Client.h>
// #include <DHT.h>                // Install DHT library by adafruit 1.3.8
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_NeoPixel.h>

// #define DHT_SENSOR_PIN 4
// #define DHT_SENSOR_TYPE DHT11


const int oneWireBus = 4;
const int turbidityPin = A0;  // Connect turbidity sensor to A0
const float turbidityConversion = 5.0 / 1024.0 * 3;
const int relayPin = 22;  // Connect relay to GPIO 22 on ESP32

// Motor Pins
const int MOTOR1_PIN = 33;  // ESP32 pin GPIO16, which connects to the first motor via a relay
const int MOTOR2_PIN = 32;  // ESP32 pin GPIO17, which connects to the second motor via a relay


OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);



#define LedPin 16      // pin d0 as toggle pin
#define NUM_PIXELS 8   //number of rgb led
#define PIN_PIXELS 14  //pin d5 as neopixel input


//To provide the ESP32 / ESP8266 with the connection and the sensor type
// DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "Anshuman's S22"
#define WIFI_PASSWORD "sabx7164"

// Insert Firebase project API Key
#define API_KEY "AIzaSyC7eLfOI2WLsymgPv_yRIxYnlPgwT4QVCA"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "iot-project-a3829-default-rtdb.asia-southeast1.firebasedatabase.app"

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;  //since we are doing an anonymous sign in

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, PIN_PIXELS, NEO_GRB + NEO_KHZ800);


void setup() {

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);  // Turn on the air pump


  //dht_sensor.begin();
  pinMode(LedPin, OUTPUT);
  pixels.begin();

  sensors.begin();
  Serial.begin(115200);



  // Initialize Motor Pins
  pinMode(MOTOR1_PIN, OUTPUT);
  pinMode(MOTOR2_PIN, OUTPUT);


  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback;  //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {

  //temperature and humidity measured should be stored in variables so the user
  //can use it later in the database

  int turbidity = analogRead(turbidityPin);
  float turbidityVoltage = turbidity * turbidityConversion;
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);

  // float temperature = dht_sensor.readTemperature();
  // float humidity = dht_sensor.readHumidity();

  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)) {
    //since we want the data to be updated every second
    sendDataPrevMillis = millis();
    // Enter Temperature in to the DHT_11 Table
    if (Firebase.RTDB.setInt(&fbdo, "DS18b20/Temperature", temperature)) {
      // This command will be executed even if you dont serial print but we will make sure its working
      Serial.print("Temperature : ");
      Serial.println(temperature);
    } else {
      Serial.println("Failed to Read from the Sensor");
      Serial.println("REASON: " + fbdo.errorReason());
    }


    // Enter Humidity in to the DHT_11 Table
    if (Firebase.RTDB.setFloat(&fbdo, "Turbidity/Turbidity_Voltage", turbidityVoltage)) {
      Serial.print("turbidityVoltage : ");
      Serial.print(turbidityVoltage);
    } else {
      Serial.println("Failed to Read from the Sensor");
      Serial.println("REASON: " + fbdo.errorReason());
    }

    // if (Firebase.RTDB.getBool(&fbdo, "M1Status")) {
    //   bool M1state = fbdo.boolData();
    //   digitalWrite(MOTOR1_PIN, M1state);
    // }
    // if (Firebase.RTDB.getBool(&fbdo, "M2Status")) {
    //   bool M2state = fbdo.boolData();
    //   digitalWrite(MOTOR2_PIN, M2state);
    // }


    // Air Pump is always on
    //delay(1000);  // Poll Firebase periodically



    if (Firebase.RTDB.getString(&fbdo, "/M1Status")) {
      String MOTORstatus1 = fbdo.stringData();
      if (MOTORstatus1.toInt() == 1) {
        Serial.println("Motor1 on");
        digitalWrite(MOTOR1_PIN, HIGH);
      } else {
        Serial.println("Motor1 off");
        digitalWrite(MOTOR1_PIN, LOW);
      }
    } else {
      Serial.print("Error in getString (M1Status), ");
      Serial.println(fbdo.errorReason());
    }

    if (Firebase.RTDB.getString(&fbdo, "/M2Status")) {
      String MOTORstatus2 = fbdo.stringData();
      if (MOTORstatus2.toInt() == 1) {
        Serial.println("Motor2 on");
        digitalWrite(MOTOR2_PIN, HIGH);
      } else {
        Serial.println("Motor2 off");
        digitalWrite(MOTOR2_PIN, LOW);
      }
    } else {
      Serial.print("Error in getString (M2Status), ");
      Serial.println(fbdo.errorReason());
    }
  }
}
