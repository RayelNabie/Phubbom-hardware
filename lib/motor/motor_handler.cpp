//
// Created by Rayel Nabie on 31/05/2026.
//

#include "motor_handler.h"

#ifdef UNIT_TEST
#include "stubs.h"
#else
#include <Arduino.h>
#endif

#include "hw_config.h"

unsigned long MotorHandler::pulseStartTime = 0;
unsigned long MotorHandler::pulseDuration = 0;
bool MotorHandler::isPulsing = false;

void MotorHandler::on() {
    analogWrite(MOTOR_PIN, 0);
}

void MotorHandler::off() {
    analogWrite(MOTOR_PIN, 255);
}

void MotorHandler::pulse(unsigned long durationMs) {
    pulseStartTime = millis();
    pulseDuration = durationMs;
    isPulsing = true;
    on();
}

void MotorHandler::update() {
    if (!isPulsing) return;
    
    if (millis() - pulseStartTime >= pulseDuration) {
        off();
        isPulsing = false;
    }
}

bool MotorHandler::isPulseActive() {
    return isPulsing;
}
