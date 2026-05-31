#ifndef LED_HANDLER_H
#define LED_HANDLER_H

#include "hw_config.h"

class LEDHandler {
public:
  static void on()  { analogWrite(LED_PIN, 0); }
  static void off() { analogWrite(LED_PIN, 255); }
};

#endif
