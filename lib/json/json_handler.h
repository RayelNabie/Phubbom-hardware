#ifndef JSON_HANDLER_H
#define JSON_HANDLER_H

#include <ArduinoJson.h>
#include "config.h"

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

    if (!doc["audio"].is<const char*>() || !doc["countdown"].is<int>()) {
      Serial.println("missing fields in JSON");
      state = JSON_MISSING_FIELDS;
      return;
    }

    state = JSON_VALID;
    Serial.println(" JSON valid!");
  }

  bool isValid() const {
    return state == JSON_VALID;
  }
};

#endif
