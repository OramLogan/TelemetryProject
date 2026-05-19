#include"gtest/gtest.h"
#include"TelementaryStore.h"
#include"TelemetryMessage.h"
#include<thread>
#include<vector>

using namespace telementary;

TEST(TelemetryStoreTest, TelemetryStoreBasic)
{
    TelemetryMessage msg1("SAT1", 3500, 25);
    TelemetryMessage msg2("SAT3", 4000, 0);

    TelementaryStore store;
    store.addMessage(msg1);
    store.addMessage(msg2);

    auto messages = store.getAll();

    EXPECT_EQ(messages.size(), 2);
    EXPECT_EQ(messages[0].getSatelliteId(), "SAT1");
    EXPECT_EQ(messages[1].getSatelliteId(), "SAT3");
}



TEST(TelemetryStoreTest, TelementaryThreads)
{
    TelementaryStore store;
    auto worker = [](TelementaryStore& store, int id)
    {
        for(int i = 1; i < 1001; i++)
        {
            store.addMessage({"SAT" + std::to_string(id), i, (double)50});
        }
    };

    std::vector<std::thread> threads;

    for(int i = 0; i < 4; i++)
    {
        threads.emplace_back(worker, std::ref(store), i);
    }

    for(auto& t: threads)
    {
        t.join();
    }

    EXPECT_EQ(store.size(), 4000);
}