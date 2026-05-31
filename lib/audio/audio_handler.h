#ifndef AUDIO_HANDLER_H
#define AUDIO_HANDLER_H

class AudioHandler {
public:
  static void playSuccess();
  static void playError();

private:
  static void playTone(int frequency, int duration);
};

#endif
