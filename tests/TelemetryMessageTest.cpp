#include<gtest/gtest.h>
#include"TelemetryMessage.h"

using namespace telementary;

TEST(TelemetryMessageTest, TelemetryMessageBasic)
{
    TelemetryMessage msg = {"SAT1", 0500, 21.0};

    EXPECT_EQ(msg.getSatelliteId(), "SAT1");
    EXPECT_EQ(msg.getTimeStamp(), 0500);
    EXPECT_EQ(msg.getTemperature(), 21.0);
}