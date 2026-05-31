#ifdef UNIT_TEST
#include "stubs.h"
#else
#include <Arduino.h>
#endif

#include "json_handler.h"

JSONHandler::JSONHandler(const char* data) : jsonData(data) {}

void JSONHandler::validate() {
  JsonDocument doc;
  const DeserializationError error = deserializeJson(doc, jsonData);

  if (error) {
    Serial.println(error.c_str());
    state = JSON_PARSE_ERROR;
    return;
  }

  if (!doc["audio"].is<const char*>() || !doc["countdown"].is<int>()) {
    state = JSON_MISSING_FIELDS;
    return;
  }

  state = JSON_VALID;
}

bool JSONHandler::isValid() const {
  return state == JSON_VALID;
}
