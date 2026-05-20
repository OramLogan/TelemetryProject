#ifndef ITELEMETRYSTORE_H
#define ITELEMETRYSTORE_H

#include"TelemetryMessage.h"
#include<vector>

namespace telementary
{
    class ITelemetryStore
    {
        public:
            virtual void addMessage(const TelemetryMessage& msg) = 0;

            virtual std::vector<TelemetryMessage> getAll() const = 0;

            virtual std::size_t size() const = 0;

            virtual ~ITelemetryStore() = default;
    };
}

#endif