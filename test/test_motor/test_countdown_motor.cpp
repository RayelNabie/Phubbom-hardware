#include <gtest/gtest.h>
#include "stubs.h"
#include "hw_config.h"
#include <countdown_manager.h>
#include <motor_handler.h>

// Test that countdown triggers motor on/off
TEST(CountdownMotor, MotorTogglesWithCountdown) {
    CountdownManager countdown;
    g_analogWrites.clear();
    g_millis = 1000;
    
    // Start countdown
    countdown.start();
    
    // First update at ~500ms into phase 1 - motor should turn on
    g_millis = 1500;
    countdown.update();
    
    // Check motor was turned on (value 0)
    bool motorOn = false;
    for (auto& write : g_analogWrites) {
        if (write.first == MOTOR_PIN && write.second == 0) {
            motorOn = true;
        }
    }
    EXPECT_TRUE(motorOn) << "Motor should turn on during countdown";
}

// Test that motor turns off at end of countdown
TEST(CountdownMotor, MotorTurnsOffAfterDuration) {
    CountdownManager countdown;
    g_analogWrites.clear();
    g_millis = 1000;
    
    countdown.start();
    g_millis = 35000;  // Well past 30s duration
    countdown.update();
    
    // Check motor was turned off (value 255)
    bool motorOff = false;
    for (auto& write : g_analogWrites) {
        if (write.first == MOTOR_PIN && write.second == 255) {
            motorOff = true;
        }
    }
    EXPECT_TRUE(motorOff) << "Motor should turn off when countdown ends";
}
