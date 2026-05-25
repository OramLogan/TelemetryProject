#pragma once
#include<string>

namespace telementary
{
    struct dbConfiguration
    {
        std::string host;
        std::string port;
        std::string name;
        std::string user;
        std::string password;

        std::string loadConfiguration() const;
        
    };

    dbConfiguration loadDBconfig();
    
}