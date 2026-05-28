#ifndef GPIO_MANAGER_H
#define GPIO_MANAGER_H

#include "config.h"

// Encapsulation Pattern: Alle GPIO zaken hier
class GPIOManager {
public:
  void init() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(BUZZER_PIN, OUTPUT);
  }

  void setBuzzer(bool state) {
    digitalWrite(BUZZER_PIN, state ? HIGH : LOW);
  }
};

#endif
