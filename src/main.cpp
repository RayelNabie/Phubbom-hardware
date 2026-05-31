#include <Arduino.h>
#include "system_manager.h"

AudioSystem audioSystem;

void setup() {
  Serial.begin(115200);
  delay(500);
  audioSystem.initialize();
}

void loop() {
  audioSystem.update();
}
