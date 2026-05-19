#ifndef TELEMENTARYSTORE_H
#define TELEMENTARYSTORE_H

#include"TelemetryMessage.h"
#include<vector>
#include<cstddef>
#include<mutex>


namespace telementary
{
    class TelementaryStore
    {
        private:
            std::vector<TelemetryMessage> msg_store;
            mutable std::mutex _mutex;

        public:
            void addMessage(const TelemetryMessage& msg);
            const std::vector<TelemetryMessage>& getAll() const;
            std::size_t size() const;
    };
}



#endif