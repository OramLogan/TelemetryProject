#pragma once
#include<condition_variable>
#include<string>
#include<mutex>
#include<queue>
#include<memory>
#include<pqxx/pqxx>

namespace telementary
{
    class DatabaseConnectionPool
    {
        private:
            std::queue<std::unique_ptr<pqxx::connection>> connections;
            std::mutex _mutex;
            std::condition_variable _cv;

        public:
            DatabaseConnectionPool(const std::string& connectionString, std::size_t poolSize);
            std::unique_ptr<pqxx::connection> acquire();
            void release(std::unique_ptr<pqxx::connection> conn);

            bool isEmpty() const;
    };
}