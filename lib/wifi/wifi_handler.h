//
// WiFi & API Handler for Phubbom
// Fetches question data from endpoint
//

#ifndef PHUBBOM_HARDWARE_WIFI_HANDLER_H
#define PHUBBOM_HARDWARE_WIFI_HANDLER_H

#include <ArduinoJson.h>

#ifdef UNIT_TEST
#include <string>
using WiFiString = std::string;
#else
using WiFiString = String;
#endif

struct QuestionData {
    unsigned long countdown;
    WiFiString audioUrl;
};

class WiFiHandler {
public:
    static void initialize();
    static bool fetchQuestion(QuestionData& data);
    static bool downloadAudio(const WiFiString& url, const WiFiString& savePath);
    static bool isConnected();
    
private:
    static const char* API_ENDPOINT;
};

#endif //PHUBBOM_HARDWARE_WIFI_HANDLER_H
