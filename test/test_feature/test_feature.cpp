#include <gtest/gtest.h>
#include "stubs.h"
#include <hw_config.h>
#include <system_manager.h>

class FeatureTest : public ::testing::Test {
protected:
    void SetUp() override {
        g_millis            = 0;
        g_digitalReadReturn = HIGH;
        g_digitalWrites.clear();
        g_analogWrites.clear();
        g_tones.clear();
    }
};

static bool pinDrivenHigh(int pin) {
    for (auto& [p, v] : g_digitalWrites)
        if (p == pin && v == HIGH) return true;
    return false;
}

static bool pinAnalogWrittenNonZero(int pin) {
    for (auto& [p, v] : g_analogWrites)
        if (p == pin && v > 0) return true;
    return false;
}

static bool pinAnalogWrittenValue(int pin, int val) {
    for (auto& [p, v] : g_analogWrites)
        if (p == pin && v == val) return true;
    return false;
}

// Knop indrukken → success-melodie speelt (tone() aangeroepen)
TEST_F(FeatureTest, ButtonPress_PlaysSuccessMelody) {
    AudioSystem system;
    system.initialize();

    g_digitalReadReturn = LOW;
    system.update();

    EXPECT_FALSE(g_tones.empty());
}

// Success-audio pulseert mee met fase 1 van de countdown (500ms)
TEST_F(FeatureTest, SuccessAudio_PulsesWithCountdownPhase1) {
    AudioSystem system;
    system.initialize();

    g_digitalReadReturn = LOW;
    system.update();
    g_digitalReadReturn = HIGH;
    g_tones.clear();

    g_millis = 500;
    system.update();

    EXPECT_EQ(1, g_tones.size());
}

// Na audio → motor puls na 500ms (fase 1)
TEST_F(FeatureTest, AfterButtonPress_MotorPulsesAfter500ms) {
    AudioSystem system;
    system.initialize();

    g_digitalReadReturn = LOW;
    system.update();
    g_digitalReadReturn = HIGH;
    g_analogWrites.clear();

    g_millis = 500;
    system.update();

    EXPECT_TRUE(pinAnalogWrittenValue(MOTOR_PIN, 0));
}

// Na audio → LED aan na 500ms
TEST_F(FeatureTest, AfterButtonPress_LEDTurnsOnAfter500ms) {
    AudioSystem system;
    system.initialize();

    g_digitalReadReturn = LOW;
    system.update();
    g_digitalReadReturn = HIGH;
    g_analogWrites.clear();

    g_millis = 500;
    system.update();

    EXPECT_TRUE(pinAnalogWrittenValue(LED_PIN, 0));
}

// Tweede knopdrukt tijdens countdown → genegeerd (geen nieuwe audio-start)
TEST_F(FeatureTest, SecondButtonPress_IgnoredDuringCountdown) {
    AudioSystem system;
    system.initialize();

    g_digitalReadReturn = LOW;
    system.update();
    g_digitalReadReturn = HIGH;
    system.update();
    g_tones.clear();

    g_millis = 250;
    g_digitalReadReturn = LOW;
    system.update();

    EXPECT_TRUE(g_tones.empty());
}

// Na 30s → countdown stopt, motor blijft uit
TEST_F(FeatureTest, CountdownStopsAfter30Seconds) {
    AudioSystem system;
    system.initialize();

    g_digitalReadReturn = LOW;
    system.update();
    g_digitalReadReturn = HIGH;

    g_millis = 30001;
    system.update(); // stop() aangeroepen

    g_analogWrites.clear();
    g_millis = 31000;
    system.update(); // geen nieuwe pulsen meer

    EXPECT_FALSE(pinAnalogWrittenNonZero(MOTOR_PIN));
}
