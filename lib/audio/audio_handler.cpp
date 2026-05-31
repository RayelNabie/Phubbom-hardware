#ifdef UNIT_TEST
#include "stubs.h"
#else
#include <Arduino.h>
#endif

#include "audio_handler.h"
#include "countdown_manager.h"
#include "hw_config.h"

namespace {
constexpr int SUCCESS_FREQUENCY = 1800;
constexpr unsigned long SUCCESS_TONE_DURATION_MS = 15;
}

bool AudioHandler::successActive = false;
unsigned long AudioHandler::successStartTime = 0;
unsigned long AudioHandler::lastSuccessToneTime = 0;

void AudioHandler::playSuccess() {
  startSuccess();
}

void AudioHandler::startSuccess() {
  successStartTime = millis();
  lastSuccessToneTime = successStartTime;
  successActive = true;
  playTone(SUCCESS_FREQUENCY, SUCCESS_TONE_DURATION_MS);
}

void AudioHandler::stopSuccess() {
  successActive = false;
  noTone(BUZZER_PIN);
}

bool AudioHandler::isSuccessActive() {
  return successActive && (millis() - successStartTime < CountdownManager::duration());
}

void AudioHandler::update() {
  if (!isSuccessActive()) {
    if (successActive) stopSuccess();
    return;
  }

  const unsigned long now = millis();
  const unsigned long elapsed = now - successStartTime;
  const unsigned long halfPeriod =
      CountdownManager::halfPeriodForPhase(CountdownManager::phaseForElapsed(elapsed));

  if (now - lastSuccessToneTime >= halfPeriod) {
    playTone(SUCCESS_FREQUENCY, SUCCESS_TONE_DURATION_MS);
    lastSuccessToneTime = now;
  }
}

void AudioHandler::playError() {
  playTone(500, 200);
  delay(250);
  playTone(400, 200);
  delay(250);
  playTone(300, 300);
  delay(350);
}

void AudioHandler::playTone(const int frequency, const unsigned long duration) {
  tone(BUZZER_PIN, frequency, duration);
}
