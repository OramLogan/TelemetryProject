#ifndef TELEMETRYPIPELINE_H
#define TELEMETRYPIPELINE_H

#include"TelemetryQueue.h"
#include"InMemoryTelemetryStore.h"
#include"TelemetryDatabaseStore.h"
#include"TelemetryProcessor.h"
#include"TelemetryProducer.h"
#include"TelemetryLogger.h"
#include<thread>

namespace telementary
{
    class TelemetryPipeline
    {
        private:
            TelemetryQueue queue;
            InMemoryTelemetryStore memoryStore;
            TelemetryDatabaseStore databaseStore;
            TelemetryLogger logger;

            int numProducers;
            int numProcessors;
            int numMessages;

            std::vector<TelemetryProducer> producers;
            std::vector<TelemetryProcessor> processors;

            std::vector<std::thread> producerThreads;
            std::vector<std::thread> processorThreads;

            std::vector<std::promise<int>> invalidCountPromises;
            std::vector<std::future<int>> invlaidCountFutures;

        public:
            TelemetryPipeline(int num_producers, int num_processors, int num_messages);
            void start();
            void wait();
            void stop();
            const InMemoryTelemetryStore& getInMemoryStore() const;
            const TelemetryDatabaseStore& getDatabaseStore() const;
            void submitMessage(const TelemetryMessage& msg);
            int getTotalInvalidMessages();
            void makeLog(const std::string& error_msg, const TelemetryMessage& msg);
            void makeLog(const std::string& error_msg);
            std::string readLog();

    };
}






#endif