#ifndef JSON_HANDLER_H
#define JSON_HANDLER_H

#include <ArduinoJson.h>
#include "config.h"

// State Pattern: JSON validation state
enum JSONState {
  JSON_INVALID,
  JSON_VALID,
  JSON_PARSE_ERROR,
  JSON_MISSING_FIELDS
};

class JSONHandler {
private:
  const char* jsonData = R"({
    "audio": "example.wav",
    "countdown": 10
  })";

  JSONState state = JSON_INVALID;
  String audioFile = "";
  int countdownValue = 0;

public:
  void validate() {
    Serial.println("\ncontrolling JSON...");

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, jsonData);

    if (error) {
      Serial.print(" JSON parse error: ");
      Serial.println(error.c_str());
      state = JSON_PARSE_ERROR;
      return;
    }

    if (!doc.containsKey("audio") || !doc.containsKey("countdown")) {
      Serial.println("missing fields in JSON");
      state = JSON_MISSING_FIELDS;
      return;
    }

    audioFile = doc["audio"].as<String>();
    countdownValue = doc["countdown"];
    state = JSON_VALID;

    Serial.println(" JSON valid!");
    Serial.print("  Audio: ");
    Serial.println(audioFile);
    Serial.print("  Countdown: ");
    Serial.println(countdownValue);
  }

  bool isValid() const {
    return state == JSON_VALID;
  }
};

#endif
