//
// DFPlayer Mini MP3 Module Handler
// Created by Rayel Nabie on 31/05/2026
//

#ifndef PHUBBOM_HARDWARE_DFPLAYER_HANDLER_H
#define PHUBBOM_HARDWARE_DFPLAYER_HANDLER_H

class DFPlayerHandler {
public:
    static void initialize();
    static void playTrack(int trackNumber);
    static void stop();
    static void setVolume(int volume);
    static bool isInitialized();

private:
    static bool initialized;
};

#endif //PHUBBOM_HARDWARE_DFPLAYER_HANDLER_H
