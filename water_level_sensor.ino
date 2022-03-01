#include<WiFi.h>
#include "ThingSpeak.h"
#define CHANNEL_ID 1658804 //Your Channel ID
#define CHANNEL_API_KEY "GNBQRPWEBW3XJWP8" //Your Channel API Key
WiFiClient client;
#define POWER_PIN  17 // ESP32 pin GIOP17 connected to sensor's VCC pin
#define SIGNAL_PIN 35 // ESP32 pin GIOP36 (ADC0) connected to sensor's signal pin
const char* ssid= "Your SSID Name";
const char* password= "Your Password";
#define WIFI_TIMEOUT_MS 20000
int value = 0; // variable to store the sensor value
void ConnecttoWiFi(){
   Serial.print("Connecting to WiFi");
   WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    unsigned long startAttemptTime= millis();
    while(WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT_MS)
    {
      Serial.print(".");
      delay(100);
      }
  if(WiFi.status()!= WL_CONNECTED)
  {
     Serial.println("Failed!");
    }else{
      Serial.print("Connected!");
       Serial.println(WiFi.localIP());
      }
  }
void setup() {
    pinMode(POWER_PIN, OUTPUT);   // configure pin as an OUTPUT
  digitalWrite(POWER_PIN, LOW); // turn the sensor OFF
  Serial.begin(9600);
  ConnecttoWiFi();
  ThingSpeak.begin(client);  
}

void loop() {
  value++;
  ThingSpeak.writeField(CHANNEL_ID,1,value, CHANNEL_API_KEY);
  digitalWrite(POWER_PIN, HIGH);  // turn the sensor ON
  delay(10);                      // wait 10 milliseconds
  value = analogRead(SIGNAL_PIN); // read the analog value from sensor
  digitalWrite(POWER_PIN, LOW);   // turn the sensor OFF

  Serial.print("The water sensor value: ");
  Serial.println(value);

  delay(1000);

}
