#ifdef UNIT_TEST
#include "stubs.h"
#else
#include <Arduino.h>
#endif

#include "system_manager.h"
#include "hw_config.h"
#include "gpio_manager.h"
#include "motor_handler.h"

void AudioSystem::initialize() {
  if (systemInitialized) return;
  GPIOManager::init();
  jsonHandler.validate();
#ifdef FEATURE_DFPLAYER
  DFPlayerHandler::initialize();
#endif

#ifdef FEATURE_WIFI
  WiFiHandler::initialize();
  delay(2000);
  
  // Fetch question from API
  if (WiFiHandler::fetchQuestion(currentQuestion)) {
    Serial.println("Question fetched successfully");
    // Download audio file
    if (WiFiHandler::downloadAudio(currentQuestion.audioUrl, "/MP3/0001.wav")) {
      Serial.println("Audio downloaded successfully");
    }
  } else {
    Serial.println("Failed to fetch question");
  }
#endif

  systemInitialized = true;
}

void AudioSystem::update() {
  handleButtonInput();
#ifdef FEATURE_AUDIO
  AudioHandler::update();
#endif
#ifdef FEATURE_MOTOR
  MotorHandler::update();
#endif
#ifdef FEATURE_COUNTDOWN
  countdown.update();
#endif
}

void AudioSystem::handleButtonInput() {
  const bool buttonState = digitalRead(BUTTON_PIN) == LOW;
  if (buttonState && !buttonPressed) {
    buttonPressed = true;
    onButtonPressed();
  } else if (!buttonState) {
    buttonPressed = false;
  }
}

void AudioSystem::onButtonPressed() {
#ifdef FEATURE_COUNTDOWN
  if (countdown.isActive()) return;
#endif

  if (jsonHandler.isValid()) {
#ifdef FEATURE_COUNTDOWN
    countdown.start(currentQuestion.countdown);
#endif
#ifdef FEATURE_DFPLAYER
    DFPlayerHandler::playTrack(1);
#endif
#ifdef FEATURE_AUDIO
    AudioHandler::startSuccess();
#endif
  } else {
#ifdef FEATURE_AUDIO
    AudioHandler::playError();
#endif
#ifdef FEATURE_COUNTDOWN
    countdown.start(currentQuestion.countdown);
#endif
  }
}
