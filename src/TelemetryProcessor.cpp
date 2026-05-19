#include"TelemetryProcessor.h"
#include<iostream>
#include<stdexcept>

namespace telementary
{
    TelemetryProcessor::TelemetryProcessor(TelemetryQueue& queue, TelementaryStore& store, TelemetryLogger& logger, std::promise<int>& invalidCountPromise)
        : queue(queue), store(store), logger(logger), invalidCountPromise(invalidCountPromise) {}
    
    void TelemetryProcessor::run()
    {
        int invalidCount = 0;
        while(true)
        {
            auto msg = queue.pop();
            if(msg.getSatelliteId() == "STOP")
            {
                break;
            }

            try
            {
                store.addMessage(msg);
            }
            catch(const std::exception& e)
            {
                invalidCount++;
                logger.logError(e.what(), msg);
            }
        }
        invalidCountPromise.set_value(invalidCount);
    }
}