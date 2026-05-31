#ifndef AUDIO_HANDLER_H
#define AUDIO_HANDLER_H

class AudioHandler {
public:
  static void playSuccess();
  static void playError();
  static void startSuccess();
  static void stopSuccess();
  static void update();
  static bool isSuccessActive();

private:
  static bool successActive;
  static unsigned long successStartTime;
  static unsigned long lastSuccessToneTime;

  static void playTone(int frequency, unsigned long duration);
};

#endif
