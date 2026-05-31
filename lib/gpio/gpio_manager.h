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
    pinMode(MOTOR_PIN, OUTPUT);
    analogWrite(MOTOR_PIN, 255);
#endif
#ifdef FEATURE_LED
    pinMode(LED_PIN, OUTPUT);
    analogWrite(LED_PIN, 255);
#endif
  }
};

#endif
