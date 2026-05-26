#ifndef TELEMETRYPROCESSOR_H
#define TELEMETRYPROCESSOR_H

#include"core/ITelemetryStore.h"
#include"pipeline/TelemetryQueue.h"
#include"logger/TelemetryLogger.h"
#include<future>

namespace telementary
{
    class TelemetryProcessor
    {
        private:
            TelemetryQueue& queue;
            ITelemetryStore& memoryStore;
            ITelemetryStore& databaseStore;
            TelemetryLogger& messageLogger;
            TelemetryLogger& dbLogger;
            std::promise<int>& invalidCountPromise;

        
        public:
            TelemetryProcessor(TelemetryQueue& queue, ITelemetryStore& store, ITelemetryStore& dbStore, TelemetryLogger& messageLogger, TelemetryLogger& dbLogger, std::promise<int>& invalidCountPromise);
            void run();
    };
}



#endif