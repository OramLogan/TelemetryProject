#include"InMemoryTelemetryStore.h"
#include<stdexcept>


namespace telementary
{
    void InMemoryTelemetryStore::addMessage(const TelemetryMessage& msg)
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

    std::vector<TelemetryMessage> InMemoryTelemetryStore::getAll() const
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return msg_store;
    }

    std::size_t InMemoryTelemetryStore::size() const
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return msg_store.size();
    }
}