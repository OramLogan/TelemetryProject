#include"TelementaryStore.h"
#include<stdexcept>

namespace telementary
{
    void TelementaryStore::addMessage(const TelemetryMessage& msg)
    {
        std::lock_guard<std::mutex> lock(_mutex);

        if(msg.isValid())
        {
            msg_store.push_back(msg);
        }
        else
        {
            throw std::invalid_argument("Message is not valid");
        }
    }

    const std::vector<TelemetryMessage>& TelementaryStore::getAll() const
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return msg_store;
    }

    std::size_t TelementaryStore::size() const
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return msg_store.size();
    }
}