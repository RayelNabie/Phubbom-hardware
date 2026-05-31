#ifndef MOTOR_HANDLER_H
#define MOTOR_HANDLER_H

#include "config.h"

class MotorHandler {
public:
  void on()  { digitalWrite(MOTOR_PIN, HIGH); }
  void off() { digitalWrite(MOTOR_PIN, LOW); }
};

#endif
