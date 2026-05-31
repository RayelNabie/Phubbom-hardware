#ifdef UNIT_TEST
#include "stubs.h"
#else
#include <Arduino.h>
#endif

#include "json_handler.h"

JSONHandler::JSONHandler(const char* data) : jsonData(data) {}

void JSONHandler::validate() {
  Serial.println("\ncontrolling JSON...");

  JsonDocument doc;
  const DeserializationError error = deserializeJson(doc, jsonData);

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

bool JSONHandler::isValid() const {
  return state == JSON_VALID;
}
