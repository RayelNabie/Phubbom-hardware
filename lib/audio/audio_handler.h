#ifndef AUDIO_HANDLER_H
#define AUDIO_HANDLER_H

#include "config.h"

class AudioHandler {
public:
  AudioHandler() {}

  void playSuccess() {
    Serial.println("Playing SUCCESS melody...");
    playTone(1000, 150);
    delay(200);
    playTone(1200, 150);
    delay(200);
    playTone(1500, 300);
    delay(350);
  }

  void playError() {
    Serial.println("Playing ERROR melody...");
    playTone(500, 200);
    delay(250);
    playTone(400, 200);
    delay(250);
    playTone(300, 300);
    delay(350);
  }

private:
  void playTone(int frequency, int duration) {
    tone(BUZZER_PIN, frequency, duration);
    delay(duration);
    noTone(BUZZER_PIN);
  }
};

#endif
