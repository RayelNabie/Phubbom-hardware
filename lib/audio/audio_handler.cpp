#ifdef UNIT_TEST
#include "stubs.h"
#else
#include <Arduino.h>
#endif

#include "audio_handler.h"
#include "hw_config.h"

void AudioHandler::playSuccess() {
  Serial.println("Playing SUCCESS melody...");
  playTone(1000, 150);
  delay(200);
  playTone(1200, 150);
  delay(200);
  playTone(1500, 300);
  delay(350);
}

void AudioHandler::playError() {
  Serial.println("Playing ERROR melody...");
  playTone(500, 200);
  delay(250);
  playTone(400, 200);
  delay(250);
  playTone(300, 300);
  delay(350);
}

void AudioHandler::playTone(const int frequency, const int duration) {
  tone(BUZZER_PIN, frequency, duration);
  delay(duration);
  noTone(BUZZER_PIN);
}
