#include"TelemetryDatabaseStore.h"

namespace telementary
{
    TelemetryDatabaseStore::TelemetryDatabaseStore(const std::string& connectionString)
        : conn(connectionString)
    {
        if (!conn.is_open())
        {
            throw std::runtime_error("Could not open PostgreSQL connection");
        }
        createTable();
    }

    void TelemetryDatabaseStore::createTable()
    {
        pqxx::work txn(conn);

        txn.exec(
            "CREATE TABLE IF NOT EXISTS telemetry ("
            "id SERIAL PRIMARY KEY,"
            "satellite_id TEXT NOT NULL,"
            "timestamp BIGINT NOT NULL,"
            "temperature DOUBLE PRECISION NOT NULL"
            ")"
        );

        txn.commit();
    }

    void TelemetryDatabaseStore::addMessage(const TelemetryMessage& msg)
    {
        pqxx::work txn(conn);

        if(msg.isValid())
        {
            txn.exec_params(
                "INSERT INTO telemetry (satellite_id, timestamp, temperature) "
                "VALUES ($1, $2, $3)",
                msg.getSatelliteId(),
                msg.getTimeStamp(),
                msg.getTemperature()
            );
            txn.commit();
        }
        else
        {
            throw std::invalid_argument("Message is not valid, db insertion failed");
        }
    }

    std::vector<TelemetryMessage> TelemetryDatabaseStore::getAll() const
    {
        pqxx::work txn(conn);

        pqxx::result result = txn.exec(
            "SELECT satellite_id, timestamp, temperature,"
            "FROM telemetry,"
            "ORDER BY id ASC"
        );

        std::vector<TelemetryMessage> messages;

        for(const auto& row : result)
        {
            std::string satelliteId = row["satellite_id"].as<std::string>();
            int timestamp = row["timestamp"].as<int>();
            double temperature = row["temperature"].as<double>();

            messages.emplace_back(satelliteId, timestamp, temperature);
        }

        txn.commit();
        return messages;
    }

    std::size_t TelemetryDatabaseStore::size() const
    {
        pqxx::work txn(conn);

        pqxx::result result = txn.exec(
            "SELECT COUNT(id),"
            "FROM telemetry"
        );

        std::size_t size = result[0][0].as<std::size_t>();

        txn.commit();

        return size;
    }
}