#ifdef UNIT_TEST
#include "stubs.h"
#else
#include <Arduino.h>
#endif

#include "countdown_manager.h"
#include "hw_config.h"
#include "motor_handler.h"
#include "led_handler.h"

int CountdownManager::phaseForElapsed(unsigned long elapsed) {
  if (elapsed < 10000) return 1;
  if (elapsed < 20000) return 2;
  return 3;
}

unsigned long CountdownManager::halfPeriodForPhase(int phase) {
  if (phase == 1) return 500;
  if (phase == 2) return 250;
  return 125;
}

unsigned long CountdownManager::halfPeriod() const {
  return halfPeriodForPhase(phaseForElapsed(millis() - startTime));
}

void CountdownManager::start() {
  startTime  = millis();
  lastToggle = startTime;
  pulseState = false;
  active     = true;
}

bool CountdownManager::isActive() const {
  return active && (millis() - startTime < 30000);
}

void CountdownManager::stop() {
  active = false;
#ifdef FEATURE_MOTOR
  MotorHandler::off();
#endif
#ifdef FEATURE_LED
  LEDHandler::off();
#endif
}

void CountdownManager::update() {
  if (!isActive()) {
    if (active) stop();
    return;
  }

  const unsigned long now = millis();
  if (now - lastToggle >= halfPeriod()) {
    pulseState = !pulseState;
    if (pulseState) {
#ifdef FEATURE_MOTOR
      MotorHandler::on();
#endif
#ifdef FEATURE_LED
      LEDHandler::on();
#endif
    } else {
#ifdef FEATURE_MOTOR
      MotorHandler::off();
#endif
#ifdef FEATURE_LED
      LEDHandler::off();
#endif
    }
    lastToggle = now;
  }
}
