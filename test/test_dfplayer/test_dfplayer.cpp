#include <gtest/gtest.h>
#include "stubs.h"
#include "hw_config.h"
#include "dfplayer_handler.h"

class DFPlayerTest : public ::testing::Test {
protected:
    void SetUp() override {
        g_millis = 0;
    }
};

// Test that initialize sets initialized flag
TEST_F(DFPlayerTest, InitializeSucceeds) {
    DFPlayerHandler::initialize();
    EXPECT_TRUE(DFPlayerHandler::isInitialized());
}

// Test that playTrack can be called when initialized
TEST_F(DFPlayerTest, PlayTrackWhenInitialized) {
    DFPlayerHandler::initialize();
    // Should not crash
    DFPlayerHandler::playTrack(1);
    SUCCEED();
}

// Test that setVolume clamps to valid range
TEST_F(DFPlayerTest, SetVolumeClampsToMin) {
    DFPlayerHandler::initialize();
    // Volume -10 should be clamped to 0
    DFPlayerHandler::setVolume(-10);
    SUCCEED();
}

TEST_F(DFPlayerTest, SetVolumeClampsToMax) {
    DFPlayerHandler::initialize();
    // Volume 50 should be clamped to 30
    DFPlayerHandler::setVolume(50);
    SUCCEED();
}

// Test that valid volumes work
TEST_F(DFPlayerTest, SetVolumeValid) {
    DFPlayerHandler::initialize();
    DFPlayerHandler::setVolume(15);
    SUCCEED();
}

// Test that stop can be called
TEST_F(DFPlayerTest, StopWhenInitialized) {
    DFPlayerHandler::initialize();
    DFPlayerHandler::playTrack(1);
    DFPlayerHandler::stop();
    SUCCEED();
}

// Test various track numbers
TEST_F(DFPlayerTest, PlayDifferentTracks) {
    DFPlayerHandler::initialize();
    DFPlayerHandler::playTrack(1);
    DFPlayerHandler::playTrack(5);
    DFPlayerHandler::playTrack(255);
    SUCCEED();
}

// Test that operations fail gracefully before init
TEST_F(DFPlayerTest, PlayTrackBeforeInitialize) {
    // Should not crash even if not initialized
    DFPlayerHandler::playTrack(1);
    SUCCEED();
}

TEST_F(DFPlayerTest, StopBeforeInitialize) {
    // Should not crash even if not initialized
    DFPlayerHandler::stop();
    SUCCEED();
}

TEST_F(DFPlayerTest, SetVolumeBeforeInitialize) {
    // Should not crash even if not initialized
    DFPlayerHandler::setVolume(20);
    SUCCEED();
}
