#include"DatabaseConnectionPool.h"
#include<iostream>

namespace telementary
{
    DatabaseConnectionPool::DatabaseConnectionPool(const std::string& connectionString, std::size_t poolSize)
    {
        for(std::size_t i = 0; i < poolSize; i++)
        {
            connections.push(std::move(std::make_unique<pqxx::connection>(connectionString)));
        }
    }

    std::unique_ptr<pqxx::connection> DatabaseConnectionPool::acquire()
    {
        std::unique_lock<std::mutex> lock(_mutex);

        _cv.wait(lock, [this]()
        {
            return !connections.empty();
        });

        std::unique_ptr<pqxx::connection> result = std::move(connections.front());
        connections.pop();

        return result;
    }

    void DatabaseConnectionPool::release(std::unique_ptr<pqxx::connection> conn)
    {
        std::lock_guard<std::mutex> lock(_mutex);

        connections.push(std::move(conn));

        _cv.notify_one();
    }

    bool DatabaseConnectionPool::isEmpty() const
    {
        if(connections.empty())
        {
            return true;
        }
        return false;
    }
}