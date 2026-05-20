#ifndef TELEMETRYPROCESSOR_H
#define TELEMETRYPROCESSOR_H

#include"InMemoryTelemetryStore.h"
#include"TelemetryQueue.h"
#include"TelemetryLogger.h"
#include<future>

namespace telementary
{
    class TelemetryProcessor
    {
        private:
            TelemetryQueue& queue;
            InMemoryTelemetryStore& memoryStore;
            //DatabaseTelemetryStore databaseStore;
            TelemetryLogger& logger;
            std::promise<int>& invalidCountPromise;

        
        public:
            TelemetryProcessor(TelemetryQueue& queue, InMemoryTelemetryStore& store, TelemetryLogger& logger, std::promise<int>& invalidCountPromise);
            void run();
    };
}



#endif