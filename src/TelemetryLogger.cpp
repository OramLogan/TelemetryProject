#include"TelemetryLogger.h"
#include<iostream>
#include <filesystem>

namespace telementary
{
    TelemetryLogger::TelemetryLogger(const std::string& filepath)
        : filepath(filepath)
    {
        std::filesystem::create_directories("logs");
        logFile.open(filepath, std::ios::app);
    }

    void TelemetryLogger::logError(const std::string& msg)
    {
        std::lock_guard<std::mutex> lock(logMutex);

        if(logFile.is_open())
        {
            logFile << msg << std::endl;
        }
    }

    void TelemetryLogger::logError(const std::string& error_msg, const TelemetryMessage& msg)
    {
        std::lock_guard<std::mutex> lock(logMutex);

        if(logFile.is_open())
        {
            logFile << error_msg + "-->  " + msg.getSatelliteId() + " | " + std::to_string(msg.getTimeStamp()) + " | " + std::to_string(msg.getTemperature()) << std::endl;
        }
    }
    
    std::string TelemetryLogger::readError()
    {
        std::lock_guard<std::mutex> lock(logMutex);
        logFile.flush();

        std::ifstream readFile(filepath);
        std::string line;
        std::stringstream buffer;

        if (!readFile.is_open())
        {
            return "Could not open log file";
        }

        while (std::getline(readFile, line))
        {
            buffer << line << "\n";
        }

        std::string result = buffer.str();

        if (result.empty())
        {
            return "log file is empty";
        }

        return result;
    }
}