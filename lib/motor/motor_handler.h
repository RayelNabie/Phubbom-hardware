#ifndef MOTOR_HANDLER_H
#define MOTOR_HANDLER_H

#include "hw_config.h"

class MotorHandler {
public:
  static void on()  { analogWrite(MOTOR_PIN, 255); }
  static void off() { analogWrite(MOTOR_PIN, 0); }
};

#endif
