#include<gtest/gtest.h>
#include"TelemetryAnalyzer.h"
#include"TelementaryStore.h"

using namespace telementary;

TEST(TelemetryAnalyzerTest, MaxTemperatureBasic)
{
    TelementaryStore store;
    store.addMessage({"SAT-0", 1000, 20.0});
    store.addMessage({"SAT-1", 1001, 25.0});
    store.addMessage({"SAT-2", 1002, -20.0}); // anomaly

    TelemetryAnalyzer analyzer(store);

    EXPECT_EQ(analyzer.maxTemperature(), 25.0);
}

TEST(TelemetryAnalyzerTest, MaxTemperatureEmpty)
{
    TelementaryStore store;

    //store.addMessage({"ID_1", 1000, 23.6});

    TelemetryAnalyzer analyzer(store);

    EXPECT_THROW(analyzer.maxTemperature(), std::invalid_argument);
}