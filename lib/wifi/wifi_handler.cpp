//
// WiFi & API Handler for Phubbom
//

#ifdef UNIT_TEST
#include "stubs.h"
#else
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiManager.h>
#include <SD.h>
#endif

#include "wifi_handler.h"

const char* WiFiHandler::API_ENDPOINT = "https://phubbom.nl/api/question";

void WiFiHandler::initialize() {
#ifdef UNIT_TEST
    // Test stub - do nothing
#else
    WiFiManager wm;
    
    // Auto-connect or start config portal
    bool res = wm.autoConnect("Phubbom", "phubbom123");
    
    if (!res) {
        Serial.println("Failed to connect WiFi");
    } else {
        Serial.println("WiFi connected!");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    }
#endif
}

bool WiFiHandler::isConnected() {
#ifdef UNIT_TEST
    return true;
#else
    return WiFi.status() == WL_CONNECTED;
#endif
}

bool WiFiHandler::fetchQuestion(QuestionData& data) {
#ifdef UNIT_TEST
    // Test stub - return mock data
    data.countdown = 30000;
    data.audioUrl = "https://example.com/0001.wav";
    return true;
#else
    if (!isConnected()) {
        Serial.println("WiFi not connected");
        return false;
    }
    
    HTTPClient http;
    http.begin(API_ENDPOINT);
    
    int httpCode = http.GET();
    
    if (httpCode != HTTP_CODE_OK) {
        Serial.print("HTTP Error: ");
        Serial.println(httpCode);
        http.end();
        return false;
    }
    
    String payload = http.getString();
    http.end();
    
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, payload);
    
    if (error) {
        Serial.print("JSON parse error: ");
        Serial.println(error.c_str());
        return false;
    }
    
    data.countdown = doc["countdown"] | 30000;
    data.audioUrl = doc["audioUrl"].as<String>();
    
    Serial.print("Countdown: ");
    Serial.println(data.countdown);
    Serial.print("Audio URL: ");
    Serial.println(data.audioUrl.c_str());
    
    return true;
#endif
}

bool WiFiHandler::downloadAudio(const WiFiString& url, const WiFiString& savePath) {
#ifdef UNIT_TEST
    // Test stub - pretend download succeeded
    return true;
#else
    if (!isConnected()) {
        Serial.println("WiFi not connected");
        return false;
    }
    
    HTTPClient http;
    http.begin(url.c_str());
    http.setConnectTimeout(10000);
    
    int httpCode = http.GET();
    
    if (httpCode != HTTP_CODE_OK) {
        Serial.print("Download failed: ");
        Serial.println(httpCode);
        http.end();
        return false;
    }
    
    int len = http.getSize();
    Serial.print("File size: ");
    Serial.println(len);
    
    File file = SD.open(savePath.c_str(), FILE_WRITE);
    if (!file) {
        Serial.print("Cannot open file: ");
        Serial.println(savePath.c_str());
        http.end();
        return false;
    }
    
    WiFiClient* stream = http.getStreamPtr();
    
    uint8_t buffer[256];
    int bytesWritten = 0;
    
    while (http.connected() && (len > 0 || len == -1)) {
        size_t size = stream->available();
        if (size) {
            int c = stream->readBytes(buffer, (size > sizeof(buffer)) ? sizeof(buffer) : size);
            file.write(buffer, c);
            bytesWritten += c;
            
            if (len > 0) {
                len -= c;
            }
        }
        delay(1);
    }
    
    file.close();
    http.end();
    
    Serial.print("Downloaded: ");
    Serial.print(bytesWritten);
    Serial.println(" bytes");
    
    return true;
#endif
}
