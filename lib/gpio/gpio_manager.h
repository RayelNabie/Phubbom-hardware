#ifndef GPIO_MANAGER_H
#define GPIO_MANAGER_H

#include "config.h"

class GPIOManager {
public:
  void init() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
#ifdef FEATURE_AUDIO
    pinMode(BUZZER_PIN, OUTPUT);
#endif
#ifdef FEATURE_MOTOR
    pinMode(MOTOR_PIN, OUTPUT);
#endif
#ifdef FEATURE_LED
    pinMode(LED_R_PIN, OUTPUT);
    pinMode(LED_G_PIN, OUTPUT);
    pinMode(LED_B_PIN, OUTPUT);
#endif
  }

};

#endif
