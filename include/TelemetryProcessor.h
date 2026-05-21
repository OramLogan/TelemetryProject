#ifndef TELEMETRYPROCESSOR_H
#define TELEMETRYPROCESSOR_H

#include"ITelemetryStore.h"
#include"TelemetryQueue.h"
#include"TelemetryLogger.h"
#include<future>

namespace telementary
{
    class TelemetryProcessor
    {
        private:
            TelemetryQueue& queue;
            ITelemetryStore& memoryStore;
            ITelemetryStore& databaseStore;
            TelemetryLogger& logger;
            std::promise<int>& invalidCountPromise;

        
        public:
            TelemetryProcessor(TelemetryQueue& queue, ITelemetryStore& store, ITelemetryStore& dbStore, TelemetryLogger& logger, std::promise<int>& invalidCountPromise);
            void run();
    };
}



#endif