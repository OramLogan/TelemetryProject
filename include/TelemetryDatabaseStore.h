#ifndef TELEMETRYDATABASESTORE_H
#define TELEMETRYDATABASESTORE_H

#include"ITelemetryStore.h"
#include<string>
#include<vector>
#include<pqxx/pqxx>


namespace telementary
{
    class TelemetryDatabaseStore : public ITelemetryStore
    {
        private:
            void createTable();
            mutable pqxx::connection conn;

        public:
            explicit TelemetryDatabaseStore(const std::string& connectionString);
            void addMessage(const TelemetryMessage& msg) override;
            std::vector<TelemetryMessage> getAll() const override;
            std::size_t size() const override;
    };
}



#endif