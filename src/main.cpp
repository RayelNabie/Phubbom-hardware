#include <Arduino.h>
#include "system_manager.h"

AudioSystem manager;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("=== ESP32-C3 Audio Test System ===");

  manager.initialize();

  Serial.println("Ready! Press the button to play an audio from the json file");
}

void loop() {
  manager.update();
  delay(50);
}
