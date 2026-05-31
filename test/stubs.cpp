#include "stubs.h"
#include <gtest/gtest.h>

unsigned long                                           g_millis            = 0;
int                                                     g_digitalReadReturn = HIGH;
std::vector<std::pair<int,int>>                         g_digitalWrites;
std::vector<std::pair<int,int>>                         g_analogWrites;
std::vector<std::tuple<int,unsigned int,unsigned long>> g_tones;
SerialClass                                             Serial;
SerialClass                                             Serial1;
WiFiClass                                               WiFi;
WiFiManagerClass                                        wifiManager;

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
