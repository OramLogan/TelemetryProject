#include"TelemetryProducer.h"

namespace telementary
{
    TelemetryProducer::TelemetryProducer(TelemetryQueue& queue, int producer, int messages) 
        : queue(queue), producerId(producer), num_messages(messages) {}

    void TelemetryProducer::run() 
    {
        for(int i = 0; i < num_messages; i++)
        {
            queue.push({"SAT-" + std::to_string(producerId), i+1, (i+1)*0.1});
        }
    }
}