#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include "json_handler.h"
#include "audio_handler.h"
#include "countdown_manager.h"

class AudioSystem {
private:
  JSONHandler      jsonHandler;
  AudioHandler     audioHandler;
  CountdownManager countdown;
  bool buttonPressed     = false;
  bool systemInitialized = false;

  void handleButtonInput();
  void onButtonPressed();

public:
  void initialize();
  void update();
};

#endif
