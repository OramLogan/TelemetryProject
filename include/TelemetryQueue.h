#ifndef TELEMETRYQUEUE_H
#define TELEMETRYQUEUE_H

#pragma once
#include"TelemetryMessage.h"
#include<mutex>
#include<queue>
#include<condition_variable>
#include<optional>


namespace telementary
{
    class TelemetryQueue
    {
        private:
            std::queue<TelemetryMessage> _queue;
            mutable std::mutex _mutex;
            std::condition_variable _cv;
        
        public:
            void push(const TelemetryMessage& msg);
            TelemetryMessage pop();
            bool empty() const;
    };
}


#endif