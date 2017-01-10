#include "MOSTLora.h"
#include "MLPacketParser.h"

#define LED_PIN 13

MOSTLora lora;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  lora.begin();
  lora.writeConfig(915000, 0, 0, 7, 5);
  lora.setMode(E_LORA_POWERSAVING);     // module mode: power-saving
  lora.setCallbackPacketReqData(blink); // set polling request callback
}

void loop() {
  lora.run(); // lora handle input message
  delay(100);
}

// Callback method when getting request packet from a station gateway
void blink(unsigned char* data, int szData) {
  for (int i=0; i<10; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
}

