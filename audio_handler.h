#ifndef AUDIO_HANDLER_H
#define AUDIO_HANDLER_H

#include "config.h"
#include "gpio_manager.h"

// Strategy Pattern: verschillende geluid-strategieën
class AudioHandler {
private:
  GPIOManager* gpio;

public:
  AudioHandler(GPIOManager* gpioManager) : gpio(gpioManager) {}

  void playSuccess() {
    Serial.println("Playing SUCCESS melody...");
    playTone(200);
    delay(100);
    playTone(200);
    delay(100);
    playTone(300);
    delay(200);
  }

  void playError() {
    Serial.println("Playing ERROR melody...");
    for (int i = 0; i < 2; i++) {
      playTone(150);
      delay(100);
      playTone(150);
      delay(100);
    }
    playTone(300);
    delay(200);
  }

private:
  void playTone(int duration) {
    gpio->setBuzzer(true);
    delay(duration / 2);
    gpio->setBuzzer(false);
    delay(duration / 2);
  }
};

#endif
