#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include "config.h"
#include "json_handler.h"
#include "gpio_manager.h"
#include "audio_handler.h"
#include "motor_handler.h"
#include "led_handler.h"
#include "countdown_manager.h"

class AudioSystem {
private:
  GPIOManager      gpio;
  JSONHandler      jsonHandler;
  AudioHandler     audioHandler;
  MotorHandler     motor;
  LEDHandler       led;
  CountdownManager countdown;
  bool buttonPressed     = false;
  bool systemInitialized = false;

public:
  AudioSystem()
    : countdown(&motor, &led) {}

  void initialize() {
    if (systemInitialized) return;
    gpio.init();
    jsonHandler.validate();
    systemInitialized = true;
  }

  void update() {
    handleButtonInput();
#ifdef FEATURE_COUNTDOWN
    countdown.update();
#endif
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
#ifdef FEATURE_COUNTDOWN
    if (countdown.isActive()) return;
#endif

    Serial.println("Button pressed");

    if (jsonHandler.isValid()) {
#ifdef FEATURE_AUDIO
      audioHandler.playSuccess();
#endif
    } else {
#ifdef FEATURE_AUDIO
      audioHandler.playError();
#endif
    }

#ifdef FEATURE_COUNTDOWN
    countdown.start();
#endif
  }
};

#endif
