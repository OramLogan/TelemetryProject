#ifndef TELEMETRYPIPELINE_H
#define TELEMETRYPIPELINE_H

#include"pipeline/TelemetryQueue.h"
#include"storage/InMemoryTelemetryStore.h"
#include"storage/TelemetryDatabaseStore.h"
#include"pipeline/TelemetryProcessor.h"
#include"pipeline/TelemetryProducer.h"
#include"logger/TelemetryLogger.h"
#include<thread>

namespace telementary
{
    class TelemetryPipeline
    {
        private:
            TelemetryQueue queue;
            InMemoryTelemetryStore memoryStore;
            TelemetryDatabaseStore databaseStore;
            TelemetryLogger messageLogger;
            TelemetryLogger dbLogger;

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
            std::string readMessageLog();
            std::string readDbLog();

    };
}






#endif