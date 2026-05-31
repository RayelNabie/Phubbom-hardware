#include <gtest/gtest.h>
#include "stubs.h"
#include <countdown_manager.h>

TEST(CountdownPhase, Phase1Before10s) {
    EXPECT_EQ(1, CountdownManager::phaseForElapsed(0));
    EXPECT_EQ(1, CountdownManager::phaseForElapsed(5000));
    EXPECT_EQ(1, CountdownManager::phaseForElapsed(9999));
}

TEST(CountdownPhase, Phase2Between10sAnd20s) {
    EXPECT_EQ(2, CountdownManager::phaseForElapsed(10000));
    EXPECT_EQ(2, CountdownManager::phaseForElapsed(15000));
    EXPECT_EQ(2, CountdownManager::phaseForElapsed(19999));
}

TEST(CountdownPhase, Phase3After20s) {
    EXPECT_EQ(3, CountdownManager::phaseForElapsed(20000));
    EXPECT_EQ(3, CountdownManager::phaseForElapsed(25000));
    EXPECT_EQ(3, CountdownManager::phaseForElapsed(29999));
}

TEST(CountdownHalfPeriod, Phase1Is500ms) {
    EXPECT_EQ(500UL, CountdownManager::halfPeriodForPhase(1));
}

TEST(CountdownHalfPeriod, Phase2Is250ms) {
    EXPECT_EQ(250UL, CountdownManager::halfPeriodForPhase(2));
}

TEST(CountdownHalfPeriod, Phase3Is125ms) {
    EXPECT_EQ(125UL, CountdownManager::halfPeriodForPhase(3));
}
