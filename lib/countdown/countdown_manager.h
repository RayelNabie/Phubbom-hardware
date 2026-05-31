#ifndef COUNTDOWN_MANAGER_H
#define COUNTDOWN_MANAGER_H

#include "config.h"
#include "motor_handler.h"
#include "led_handler.h"

class CountdownManager {
private:
  MotorHandler* motor;
  LEDHandler*   led;
  unsigned long startTime  = 0;
  unsigned long lastToggle = 0;
  bool active     = false;
  bool pulseState = false;

  unsigned long halfPeriod() {
    unsigned long elapsed = millis() - startTime;
    if (elapsed < 10000) return 500;
    if (elapsed < 20000) return 250;
    return 125;
  }

  void applyPhaseColor() {
    unsigned long elapsed = millis() - startTime;
    if (elapsed < 10000) led->setColor(false, true,  false); // groen
    else if (elapsed < 20000) led->setColor(true,  true,  false); // oranje
    else                       led->setColor(true,  false, false); // rood
  }

public:
  CountdownManager(MotorHandler* m, LEDHandler* l) : motor(m), led(l) {}

  void start() {
    startTime  = millis();
    lastToggle = startTime;
    pulseState = false;
    active     = true;
  }

  bool isActive() {
    return active && (millis() - startTime < 30000);
  }

  void stop() {
    active = false;
#ifdef FEATURE_MOTOR
    motor->off();
#endif
#ifdef FEATURE_LED
    led->off();
#endif
  }

  void update() {
    if (!isActive()) {
      if (active) stop();
      return;
    }

    unsigned long now = millis();
    if (now - lastToggle >= halfPeriod()) {
      pulseState = !pulseState;
      if (pulseState) {
#ifdef FEATURE_MOTOR
        motor->on();
#endif
#ifdef FEATURE_LED
        applyPhaseColor();
#endif
      } else {
#ifdef FEATURE_MOTOR
        motor->off();
#endif
#ifdef FEATURE_LED
        led->off();
#endif
      }
      lastToggle = now;
    }
  }
};

#endif
