#ifndef LED_HANDLER_H
#define LED_HANDLER_H

#include "config.h"

class LEDHandler {
public:
  void setColor(bool r, bool g, bool b) {
    digitalWrite(LED_R_PIN, r ? HIGH : LOW);
    digitalWrite(LED_G_PIN, g ? HIGH : LOW);
    digitalWrite(LED_B_PIN, b ? HIGH : LOW);
  }

  void off() { setColor(false, false, false); }
};

#endif
