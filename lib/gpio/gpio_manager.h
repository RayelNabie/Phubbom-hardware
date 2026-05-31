#ifndef GPIO_MANAGER_H
#define GPIO_MANAGER_H

#include "hw_config.h"

class GPIOManager {
public:
  static void init() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
#ifdef FEATURE_AUDIO
    pinMode(BUZZER_PIN, OUTPUT);
#endif
#ifdef FEATURE_MOTOR
    analogWrite(MOTOR_PIN, 0);
#endif
#ifdef FEATURE_LED
    analogWrite(LED_PIN, 255);
#endif
  }
};

#endif
