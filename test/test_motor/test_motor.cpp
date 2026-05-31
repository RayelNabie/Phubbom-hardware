#include <gtest/gtest.h>
#include "stubs.h"
#include "hw_config.h"
#include <motor_handler.h>

// Test that on() writes 0 (inverted logic)
TEST(MotorHandler, OnWritesZero) {
    g_analogWrites.clear();
    MotorHandler::on();
    ASSERT_EQ(1, g_analogWrites.size());
    EXPECT_EQ(MOTOR_PIN, g_analogWrites[0].first);
    EXPECT_EQ(0, g_analogWrites[0].second);
}

// Test that off() writes 255 (inverted logic)
TEST(MotorHandler, OffWrites255) {
    g_analogWrites.clear();
    MotorHandler::off();
    ASSERT_EQ(1, g_analogWrites.size());
    EXPECT_EQ(MOTOR_PIN, g_analogWrites[0].first);
    EXPECT_EQ(255, g_analogWrites[0].second);
}

// Test pulse starts the motor immediately
TEST(MotorHandler, PulseStartsMotor) {
    g_analogWrites.clear();
    g_millis = 1000;
    
    MotorHandler::pulse(100);
    
    ASSERT_GE(g_analogWrites.size(), 1);
    EXPECT_EQ(MOTOR_PIN, g_analogWrites[0].first);
    EXPECT_EQ(0, g_analogWrites[0].second);
    EXPECT_TRUE(MotorHandler::isPulseActive());
}

// Test pulse stops after duration
TEST(MotorHandler, PulseStopsAfterDuration) {
    g_analogWrites.clear();
    g_millis = 1000;
    
    MotorHandler::pulse(100);
    g_analogWrites.clear();
    
    // Simulate time passing - pulse should still be active
    g_millis = 1050;
    MotorHandler::update();
    EXPECT_TRUE(MotorHandler::isPulseActive());
    
    // Move past duration - pulse should stop
    g_millis = 1101;
    MotorHandler::update();
    EXPECT_FALSE(MotorHandler::isPulseActive());
    
    // Should have written 255 (off)
    ASSERT_GE(g_analogWrites.size(), 1);
    EXPECT_EQ(255, g_analogWrites.back().second);
}

// Test multiple on/off cycles
TEST(MotorHandler, MultipleOnOffCycles) {
    g_analogWrites.clear();
    
    MotorHandler::on();
    EXPECT_EQ(0, g_analogWrites.back().second);
    
    MotorHandler::off();
    EXPECT_EQ(255, g_analogWrites.back().second);
    
    MotorHandler::on();
    EXPECT_EQ(0, g_analogWrites.back().second);
    
    MotorHandler::off();
    EXPECT_EQ(255, g_analogWrites.back().second);
}
