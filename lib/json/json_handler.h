#ifndef JSON_HANDLER_H
#define JSON_HANDLER_H

#include <ArduinoJson.h>

enum JSONState {
  JSON_INVALID,
  JSON_VALID,
  JSON_PARSE_ERROR,
  JSON_MISSING_FIELDS
};

class JSONHandler {
private:
  const char* jsonData;
  JSONState   state = JSON_INVALID;

public:
  explicit JSONHandler(const char* data = R"({"audio":"example.wav","countdown":10})");
  void validate();
  bool isValid() const;
};

#endif
