#include"TelemetryDatabaseStore.h"

namespace telementary
{
    TelemetryDatabaseStore::TelemetryDatabaseStore(const std::string& connectionString)
        : connection(connectionString, POOL_SIZE)
    {
        if (connection.isEmpty())
        {
            throw std::runtime_error("PostgreSQL connection empty");
        }
        createTable();
    }

    void TelemetryDatabaseStore::createTable()
    {
        auto conn = connection.acquire();
        pqxx::work txn(*conn);

        txn.exec(
            "CREATE TABLE IF NOT EXISTS telemetry ("
            "id SERIAL PRIMARY KEY,"
            "satellite_id TEXT NOT NULL,"
            "timestamp BIGINT NOT NULL,"
            "temperature DOUBLE PRECISION NOT NULL"
            ")"
        );

        txn.commit();
        connection.release(std::move(conn));
    }

    void TelemetryDatabaseStore::addMessage(const TelemetryMessage& msg)
    {
        auto conn = connection.acquire();

        try
        {
            if(!msg.isValid())
            {
                throw std::invalid_argument("Message is not valid, db insertion failed");
            }

            pqxx::work txn(*conn);

            txn.exec_params(
                "INSERT INTO telemetry (satellite_id, timestamp, temperature) VALUES ($1, $2, $3)",
                msg.getSatelliteId(),
                msg.getTimeStamp(),
                msg.getTemperature()
            );
            txn.commit();
        }
        catch(const std::exception& e)
        {
            connection.release(std::move(conn));
            throw;
        }
        connection.release(std::move(conn));
    }

    std::vector<TelemetryMessage> TelemetryDatabaseStore::getAll() const
    {
        auto conn = connection.acquire();

        try
        {
            pqxx::work txn(*conn);

            pqxx::result result = txn.exec(
                "SELECT satellite_id, timestamp, temperature "
                "FROM telemetry"
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
        catch(const std::exception& e)
        {
            connection.release(std::move(conn));
            throw;
        }

        connection.release(std::move(conn));
    }

    std::size_t TelemetryDatabaseStore::size() const
    {
        auto conn = connection.acquire();

        try
        {
            pqxx::work txn(*conn);

            pqxx::result result = txn.exec(
                "SELECT COUNT(id) "
                "FROM telemetry"
            );

            std::size_t size = result[0][0].as<std::size_t>();

            txn.commit();
            return size;
        }
        catch(const std::exception& e)
        {
            connection.release(std::move(conn));
            throw;
        }

        connection.release(std::move(conn));
    }
}