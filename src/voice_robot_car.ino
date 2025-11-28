/* Voice-operated Robot Car 
Features:
   - Connects to Wi-Fi and subscribes to Adafruit IO MQTT feeds
   - Receives simple voice commands via Adafruit IO feeds
   - Drives motor control pins to control motion
   - Uses blocking delays for simple timed movements
   - Serial debug printing to help tune and monitor messages
*/

#include <WiFi.h>                      
#include "Adafruit_MQTT.h"             
#include "Adafruit_MQTT_Client.h"     

// WiFi Access Point
#define WLAN_SSID "Bhakti"
#define WLAN_PASS "123456789"

// Adafruit.io Setup 
#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883                   // 1883 = plain MQTT, 8883 = MQTT+SSL
#define AIO_USERNAME "Bhakti29"
#define AIO_KEY "aio_hYmy08pucL4V6HGjYjhfF78atzMw"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Define subscriptions to Adafruit IO feeds 
Adafruit_MQTT_Subscribe forward = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Forward");
Adafruit_MQTT_Subscribe back    = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/backward");
Adafruit_MQTT_Subscribe left    = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Left");
Adafruit_MQTT_Subscribe right   = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Right");
Adafruit_MQTT_Subscribe stand   = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/stand");

void MQTT_connect(); 

// Setup 
void setup() {
  Serial.begin(115200);               
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  // Initialize all outputs to LOW (motors off). 
  digitalWrite(D1, 0);
  digitalWrite(D2, 0);
  digitalWrite(D3, 0);
  digitalWrite(D4, 0);

  Serial.println(F("Adafruit MQTT demo"));
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  // Start WiFi and wait for connection
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Subscribe to the Adafruit IO feeds so we receive incoming commands
  mqtt.subscribe(&forward);
  mqtt.subscribe(&back);
  mqtt.subscribe(&left);
  mqtt.subscribe(&right);
  mqtt.subscribe(&stand);
}

// Main loop 
void loop() {
  MQTT_connect();
  // Pointer to subscription that has new data
  Adafruit_MQTT_Subscribe *subscription;
  // Read incoming subscriptions with a timeout (4 seconds)
  while ((subscription = mqtt.readSubscription(4000))) {

    // Forward command 
    if (subscription == &forward) {
      Serial.print(F("Got forward: "));
      Serial.println((char *)forward.lastread);     
      uint16_t num = atoi((char *)forward.lastread); 
      Serial.println(num);

      // If payload is 0 -> execute forward motion sequence
      if (num == 0) {
        analogWrite(D1, 1);  // motor driver input A forward 
        digitalWrite(D2, 0); // motor driver input B forward
        digitalWrite(D3, 1); 
        analogWrite(D4, 0);  
        delay(4000);         // run forward for 4 seconds 
        // Stop motors after movement
        digitalWrite(D1, 0);
        digitalWrite(D2, 0);
        digitalWrite(D3, 0);
        digitalWrite(D4, 0);
      }
      else {
        // If payload not equal to 0, ensure all relevant outputs are off
        digitalWrite(D1, 0);
        digitalWrite(D2, 0);
        digitalWrite(D3, 0);
        digitalWrite(D4, 0);
      }
    }

    // Back (reverse) command 
    else if (subscription == &back) {
      Serial.print(F("Got back: "));
      Serial.println((char *)back.lastread);
      uint16_t num = atoi((char *)back.lastread);
      Serial.println(num);

      if (num == 0) { // payload 0 -> run backward sequence
        digitalWrite(D1, 0); // set motor driver pins to reverse polarity
        digitalWrite(D2, 1);
        digitalWrite(D3, 0);
        digitalWrite(D4, 1);
        delay(7000); // reverse for 7 seconds (blocking)
        // Stop motors
        digitalWrite(D1, 0);
        digitalWrite(D2, 0);
        digitalWrite(D3, 0);
        digitalWrite(D4, 0);
      }
      else {
        digitalWrite(D1, 0);
        digitalWrite(D2, 0);
        digitalWrite(D3, 0);
        digitalWrite(D4, 0);
        delay(7000);
      }
    }

    // Left turn command 
    else if (subscription == &left) {
      Serial.print(F("Got left: "));
      Serial.println((char *)left.lastread);
      uint16_t num = atoi((char *)left.lastread);
      Serial.println(num);

      if (num == 0) {
        analogWrite(D1, 270);
        digitalWrite(D2, 0);
        digitalWrite(D3, 0);
        analogWrite(D4, 270);
        delay(4000);
        // Stop motors
        digitalWrite(D1, 0);
        digitalWrite(D2, 0);
        digitalWrite(D3, 0);
        digitalWrite(D4, 0);
      } else {
        digitalWrite(D1, 0);
        digitalWrite(D2, 0);
        digitalWrite(D3, 0);
        digitalWrite(D4, 0);
      }
    }

    // Right turn command 
    else if (subscription == &right) {
      Serial.print(F("Got Right: "));
      Serial.println((char *)right.lastread);
      uint16_t num = atoi((char *)right.lastread);
      Serial.println(num);

      if (num == 0) {
        digitalWrite(D1, 0);
        analogWrite(D2, 270);
        analogWrite(D3, 270);
        digitalWrite(D4, 0);
        delay(6000); // run for 6 seconds
        // Stop motors
        digitalWrite(D1, 0);
        digitalWrite(D2, 0);
        digitalWrite(D3, 0);
        digitalWrite(D4, 0);
      }
      else {
        digitalWrite(D1, 0);
        digitalWrite(D2, 0);
        digitalWrite(D3, 0);
        digitalWrite(D4, 0);
      }
    }

    // Stand command ----------
    else if (subscription == &stand) {
      Serial.print(F("Got stand: "));
      Serial.println((char *)stand.lastread);
      uint16_t num = atoi((char *)stand.lastread);
      Serial.println(num);
      if (num == 1) {
        digitalWrite(D1, 0);
        digitalWrite(D2, 0);
        digitalWrite(D3, 0);
        digitalWrite(D4, 0);
        delay(10000);
      } else {
        digitalWrite(D1, 0);
        digitalWrite(D2, 0);
        digitalWrite(D3, 0);
        digitalWrite(D4, 0);
        delay(10000);
      }
    } 

  } 
} 

// MQTT setup
void MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) {
    return;
  }
  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3; 
  while ((ret = mqtt.connect()) != 0) { 
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(4000);  // wait 4 seconds before retrying
       retries--;
       if (retries == 0) {
         while (1); 
       }
  }
  Serial.println("MQTT Connected!");
}
