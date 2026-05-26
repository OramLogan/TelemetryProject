#ifndef TELEMETRYDATABASESTORE_H
#define TELEMETRYDATABASESTORE_H

#include"core/ITelemetryStore.h"
#include"storage/DatabaseConnectionPool.h"
#include<string>
#include<vector>
#include<pqxx/pqxx>
#include<mutex>


namespace telementary
{
    class TelemetryDatabaseStore : public ITelemetryStore
    {
        private:
            void createTable();
            mutable DatabaseConnectionPool connection;
            static constexpr std::size_t POOL_SIZE = 3;
            mutable std::mutex _mutex;

        public:
            explicit TelemetryDatabaseStore(const std::string& connectionString);
            void addMessage(const TelemetryMessage& msg) override;
            std::vector<TelemetryMessage> getAll() const override;
            std::size_t size() const override;
    };
}



#endif