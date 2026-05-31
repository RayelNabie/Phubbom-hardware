#include <gtest/gtest.h>
#include "stubs.h"
#include <json_handler.h>

TEST(JSONHandler, ValidJSON) {
    JSONHandler h(R"({"audio":"test.wav","countdown":30})");
    h.validate();
    EXPECT_TRUE(h.isValid());
}

TEST(JSONHandler, InvalidJSONParseError) {
    JSONHandler h("{ongeldige json{{");
    h.validate();
    EXPECT_FALSE(h.isValid());
}

TEST(JSONHandler, MissingAudioField) {
    JSONHandler h(R"({"countdown":30})");
    h.validate();
    EXPECT_FALSE(h.isValid());
}

TEST(JSONHandler, MissingCountdownField) {
    JSONHandler h(R"({"audio":"test.wav"})");
    h.validate();
    EXPECT_FALSE(h.isValid());
}

TEST(JSONHandler, WrongAudioType) {
    JSONHandler h(R"({"audio":42,"countdown":30})");
    h.validate();
    EXPECT_FALSE(h.isValid());
}

TEST(JSONHandler, WrongCountdownType) {
    JSONHandler h(R"({"audio":"test.wav","countdown":"dertig"})");
    h.validate();
    EXPECT_FALSE(h.isValid());
}
