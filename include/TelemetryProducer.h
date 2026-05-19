#ifndef TELEMETRYPRODUCER_H
#define TELEMETRYPRODUCER_H

#include"TelemetryQueue.h"

namespace telementary
{
    class TelemetryProducer
    {
        private:
            TelemetryQueue& queue;
            int producerId;
            int num_messages;

        public:
            TelemetryProducer(TelemetryQueue& queue, int producer, int messages);
            void run();
    };
}








#endif