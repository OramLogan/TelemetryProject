#include"dbConfiguration.h"
#include<stdexcept>

namespace
{
    std::string getRequiredEnv(const char* key)
    {
        try
        {
            const char* value = std::getenv(key);

            if(value == nullptr)
            {
                throw std::runtime_error(std::string("missing environment variable") + key);
            }

            return std::string(value);
        }
        catch(const std::exception& e)
        {
            throw;
        }
    }
}

namespace telementary
{
    std::string dbConfiguration::loadConfiguration() const
    {
        if(host.empty() || port.empty() || name.empty() || user.empty() || password.empty())
        {
            throw std::invalid_argument("dbConfiguration failed");
        }

        std::string config = "host=" + host + " port=" + port + " dbname=" + name + " user=" + user + " password=" + password;
        return config; 
    }

    dbConfiguration loadDBconfig()
    {
        return {getRequiredEnv("DB_HOST"), getRequiredEnv("DB_PORT"), getRequiredEnv("DB_NAME"), getRequiredEnv("DB_USER"), getRequiredEnv("DB_PASSWORD")};
    }
}