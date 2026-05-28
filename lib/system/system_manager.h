#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include "config.h"
#include "json_handler.h"
#include "audio_handler.h"
#include "gpio_manager.h"

class AudioSystem {
private:
  GPIOManager gpio;
  JSONHandler jsonHandler;
  AudioHandler audioHandler;
  bool buttonPressed = false;
  bool systemInitialized = false;

public:
  AudioSystem() {}

  void initialize() {
    if (systemInitialized) return;

    gpio.init();
    jsonHandler.validate();
    systemInitialized = true;
  }

  void update() {
    handleButtonInput();
  }

private:
  void handleButtonInput() {
    bool buttonState = digitalRead(BUTTON_PIN) == LOW;
    if (buttonState && !buttonPressed) {
      buttonPressed = true;
      onButtonPressed();
    } else if (!buttonState) {
      buttonPressed = false;
    }
  }

  void onButtonPressed() {
    Serial.println("Button pressed");

    if (jsonHandler.isValid()) {
      Serial.println("JSON geldig - geluid 1 afspelen");
      audioHandler.playSuccess();
    } else {
      Serial.println("JSON ongeldig - geluid 2 afspelen");
      audioHandler.playError();
    }
  }
};

#endif
