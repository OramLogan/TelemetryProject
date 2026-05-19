#include"gtest/gtest.h"
#include"TelementaryStore.h"
#include"TelemetryMessage.h"
#include"TelemetryQueue.h"
#include<thread>
#include<vector>

using namespace telementary;

TEST(TelemetryQueueTest, TelemetryThreads)
{
    TelementaryStore store;
    TelemetryQueue queue;

    const int num_consumers = 3;
    const int num_producers = 4;
    const int num_messages = 1000;


    auto producer = [&](int id)
    {
        for(int i = 0; i < num_messages; i++)
        {
            queue.push({"SAT-" + std::to_string(id), i+1, 75});
        }
    };

    auto consumer = [&]()
    {
        while(true)
        {
            auto msg = queue.pop();

            if(msg.getSatelliteId() == "STOP")
            {
                break;
            }
            store.addMessage(msg);
        }
    };

    std::vector<std::thread> consumers;
    for(int i = 0; i < num_consumers; i++)
    {
        consumers.emplace_back(consumer);
    }
    
    std::vector<std::thread> producers;
    for(int i = 0; i < num_producers; i++)
    {
        producers.emplace_back(producer, i);
    }

    
    for(auto& p : producers)
    {
        p.join();
    }

    for(int i = 0; i < num_consumers; i++)
    {
        queue.push({"STOP", i+1, 75});
    }

    for(auto& c : consumers)
    {
        c.join();
    }

    EXPECT_EQ(store.size(), num_producers * num_messages);
}