#ifndef TELEMETRYPROCESSOR_H
#define TELEMETRYPROCESSOR_H

#include"TelementaryStore.h"
#include"TelemetryQueue.h"
#include"TelemetryLogger.h"
#include<future>

namespace telementary
{
    class TelemetryProcessor
    {
        private:
            TelemetryQueue& queue;
            TelementaryStore& store;
            TelemetryLogger& logger;
            std::promise<int>& invalidCountPromise;

        
        public:
            TelemetryProcessor(TelemetryQueue& queue, TelementaryStore& store, TelemetryLogger& logger, std::promise<int>& invalidCountPromise);
            void run();
    };
}



#endif