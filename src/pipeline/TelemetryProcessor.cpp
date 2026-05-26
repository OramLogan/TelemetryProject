#include"pipeline/TelemetryProcessor.h"
#include<iostream>
#include<stdexcept>

namespace telementary
{
    TelemetryProcessor::TelemetryProcessor(TelemetryQueue& queue, ITelemetryStore& store, ITelemetryStore& dbStore, TelemetryLogger& messageLogger, TelemetryLogger& dbLogger, std::promise<int>& invalidCountPromise)
        : queue(queue), memoryStore(store), databaseStore(dbStore), messageLogger(messageLogger), dbLogger(dbLogger), invalidCountPromise(invalidCountPromise) {}
    
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
                databaseStore.addMessage(msg);
            }
            catch(const std::exception& e)
            {
                invalidCount++;
                dbLogger.logError(std::string("Database insert failed"), msg);
            }

            try
            {
                memoryStore.addMessage(msg);
            }
            catch(const std::exception& e)
            {
                messageLogger.logError(std::string("Cache memory insert failed"), msg);
            }
            
        }
        invalidCountPromise.set_value(invalidCount);
    }
}