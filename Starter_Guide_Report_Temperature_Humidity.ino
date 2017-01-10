
#include <DHT.h>
#include "MOSTLora.h"
#define DHT11_PIN 2

const char *THINKSPEAK_WRITE_API_KEY = "YOUR_THINGSPEAK_WRITE_API_KEY";

DHT dht(DHT11_PIN, DHT11);
MOSTLora lora;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lora.begin();
  lora.writeConfig(915000, 0, 0, 7, 5);
  lora.setMode(E_LORA_POWERSAVING);    // module mode: power-saving  
  //set callback function when receiving request from a station gateway
  lora.setCallbackPacketReqData(uploadEnvironmentData);
}

void loop() {
  lora.run();  // lora handle input messages
  delay(100);
}

// read temperature, humidity data and send them to ThinkSpeak
void uploadEnvironmentData(unsigned char* data, int szData) {
  float temperature,humidity;
  if (dht.readSensor(humidity, temperature, true)) {
    lora.sendPacketThingSpeak(THINKSPEAK_WRITE_API_KEY, temperature, humidity, 0, 0, 0, 0, 0, 0);  
  }
}

