#include <Arduino.h>
#include "system_manager.h"

AudioSystem system;

void setup() {
  Serial.begin(115200);
  system.initialize();
}

void loop() {
  system.update();
}
