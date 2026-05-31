//
// DFPlayer Mini MP3 Module Handler
// Using DFRobotDFPlayerMini library
//

#ifdef UNIT_TEST
#include "stubs.h"
#else
#include <Arduino.h>
#include "DFRobotDFPlayerMini.h"
#endif

#include "dfplayer_handler.h"
#include "hw_config.h"

bool DFPlayerHandler::initialized = false;
DFRobotDFPlayerMini dfplayer;

void DFPlayerHandler::initialize() {
    if (initialized) return;
    
    // Use UART1 (GPIO20 RX, GPIO21 TX)
    Serial1.begin(9600, SERIAL_8N1, DFPLAYER_RX_PIN, DFPLAYER_TX_PIN);
    delay(500);
    
    if (!dfplayer.begin(Serial1)) {
        Serial.println("DFPlayer Mini not detected");
        return;
    }
    
    dfplayer.volume(25);
    delay(100);
    
    initialized = true;
}

void DFPlayerHandler::playTrack(int trackNumber) {
    if (!initialized) return;
    dfplayer.play(trackNumber);
}

void DFPlayerHandler::stop() {
    if (!initialized) return;
    dfplayer.stop();
}

void DFPlayerHandler::setVolume(int volume) {
    if (!initialized) return;
    if (volume < 0) volume = 0;
    if (volume > 30) volume = 30;
    dfplayer.volume(volume);
}

bool DFPlayerHandler::isInitialized() {
    return initialized;
}
