#ifndef TELEMETRYLOGGER_H
#define TELEMETRYLOGGER_H

#include<fstream>
#include<sstream>
#include<mutex>
#include<string>
#include"core/TelemetryMessage.h"

namespace telementary
{
    class TelemetryLogger
    {
        private:
            std::ofstream logFile;
            std::mutex logMutex;
            std::string filepath;

        public:
            explicit TelemetryLogger(const std::string& filepath);
            void logError(const std::string& msg);
            void logError(const std::string& error_msg, const TelemetryMessage& msg);
            std::string readError();

    };
}



#endif