#include"TelemetryPipeline.h"

namespace telementary
{
    TelemetryPipeline::TelemetryPipeline(int num_producer, int num_processors, int num_messages)
        : databaseStore(
            "host=postgres "
            "port=5432 "
            "dbname=telemetry_db "
            "user=telemetry_user "
            "password=telemetry_password"), numProducers(num_producer), numProcessors(num_processors), numMessages(num_messages)
        {
            invalidCountPromises.reserve(numProcessors);
            invlaidCountFutures.reserve(numProcessors);
            processors.reserve(numProcessors);

            for(int i = 0; i < numProcessors; i++)
            {
                invalidCountPromises.emplace_back();
                invlaidCountFutures.push_back(invalidCountPromises.back().get_future());

                processors.emplace_back(queue, memoryStore, databaseStore, logger, invalidCountPromises.back());
            }

            producers.reserve(numProducers);

            for(int i = 0; i < numProducers; i++)
            {
                producers.emplace_back(queue, i, numMessages);
            }

        }

    void TelemetryPipeline::start()
    {
        for(auto& processor : processors)
        {
            processorThreads.emplace_back(&TelemetryProcessor::run, &processor);
        }

        for(auto& producer : producers)
        {
            producerThreads.emplace_back(&TelemetryProducer::run, &producer);
        }
    }

    void TelemetryPipeline::stop()
    {
        for(int i = 0; i < numProcessors; i++)
        {
            queue.push({"STOP", 1, 1});
        }
    }

    void TelemetryPipeline::wait()
    {
        for(auto& t : producerThreads)
        {
            if(t.joinable())
            {
                t.join();
            }
        }

        for(auto& t : processorThreads)
        {
            if(t.joinable())
            {
                t.join();
            }
        }
    }

    const InMemoryTelemetryStore& TelemetryPipeline::getInMemoryStore() const     
    {
        return memoryStore;
    }

    const TelemetryDatabaseStore& TelemetryPipeline::getDatabaseStore() const       
    {
        return databaseStore;
    }

    int TelemetryPipeline::getTotalInvalidMessages()
    {
        int total = 0;

        for(auto& future : invlaidCountFutures)
        {
            total += future.get();
        }
        return total;
    }

    void TelemetryPipeline::submitMessage(const TelemetryMessage& msg)
    {
        queue.push(msg);
    }

    void TelemetryPipeline::makeLog(const std::string& error_msg, const TelemetryMessage& msg)
    {
        logger.logError(error_msg, msg);
    }

    void TelemetryPipeline::makeLog(const std::string& error_msg)
    {
        logger.logError(error_msg);
    }

    std::string TelemetryPipeline::readLog()
    {
        return logger.readError();
    }
}