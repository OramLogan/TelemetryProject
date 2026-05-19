#include"TelemetryQueue.h"

namespace telementary
{
    void TelemetryQueue::push(const TelemetryMessage& msg){
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _queue.push(msg);
        }
        _cv.notify_one();
    }

    TelemetryMessage TelemetryQueue::pop()
    {
        std::unique_lock<std::mutex> lock(_mutex);

        _cv.wait(lock, [this]() {
            return !_queue.empty();
        });

        TelemetryMessage msg = _queue.front();
        _queue.pop();

        return msg;
    }

    bool TelemetryQueue::empty() const
    {
        std::lock_guard<std::mutex> lock(_mutex);

        return _queue.empty();
    }
}