#ifndef INMEMORYTELEMETRYSTORE_H
#define INMEMORYTELEMETRYSTORE_H

#include"core/ITelemetryStore.h"
#include<cstddef>
#include<mutex>


namespace telementary
{
    class InMemoryTelemetryStore : public ITelemetryStore
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