#ifndef INMEMORYTELEMETRYSTORE_H
#define INMEMORYTELEMETRYSTORE_H

#include"ITelemetryStore.h"
#include<cstddef>
#include<mutex>


namespace telementary
{
    class InMemoryTelemetryStore : ITelemetryStore
    {
        private:
            std::vector<TelemetryMessage> msg_store;
            mutable std::mutex _mutex;

        public:
            void addMessage(const TelemetryMessage& msg) override;
            std::vector<TelemetryMessage> getAll() const override;
            std::size_t size() const override;
    };
}



#endif