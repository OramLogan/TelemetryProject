#include"TelemetryAnalyzer.h"
#include<stdexcept>
#include<limits>

namespace telementary
{
    TelemetryAnalyzer::TelemetryAnalyzer(const ITelemetryStore& store)
    : _store(store)
    {}

    double TelemetryAnalyzer::averageTemperature() const
    {
        int size = _store.size();
        if(size == 0)
        {
            //return 0;
            throw std::invalid_argument("No Messages Found");
        }

        double avg_temperature = 0;
        auto copy = _store.getAll();

        for(const auto& msg : copy)
        {
            avg_temperature += msg.getTemperature();
        }
        avg_temperature /= size;

        return avg_temperature;
    }

    double TelemetryAnalyzer::minTemperature() const
    {
        int size = _store.size();
        if(size == 0)
        {
            //return 0;
            throw std::invalid_argument("No Messages Found");
        }

        double min_temperature = std::numeric_limits<double>::max();;
        auto copy = _store.getAll();

        for(const auto& msg : copy)
        {
            min_temperature = std::min(min_temperature, msg.getTemperature());
            
        }

        return min_temperature;
    }

    double TelemetryAnalyzer::maxTemperature() const
    {
        int size = _store.size();
        if(size == 0)
        {
            //return 0;
            throw std::invalid_argument("No Messages Found");
        }

        double max_temperature = std::numeric_limits<double>::lowest();;
        auto copy = _store.getAll();

        for(const auto& msg : copy)
        {
            max_temperature = std::max(max_temperature, msg.getTemperature());   
        }

        return max_temperature;
    }

    std::vector<TelemetryMessage> TelemetryAnalyzer::filterBySatelliteId(const std::string& satelliteId) const
    {
        int size = _store.size();
        if(size == 0)
        {
            throw std::invalid_argument("No Messages Found");
        }

        auto copy = _store.getAll();
        std::vector<TelemetryMessage> message_by_satId;

        for(const auto& msg : copy)
        {
            if(msg.getSatelliteId() == satelliteId)
            {
                message_by_satId.push_back(msg);
            }
        }

        return message_by_satId;
    }

    std::vector<TelemetryMessage> TelemetryAnalyzer::detectAnomaly(double minAllowed, double maxAllowed) const
    {
        int size = _store.size();
        if(size == 0)
        {
            throw std::invalid_argument("No Messages Found");
        }

        auto copy = _store.getAll();
        std::vector<TelemetryMessage> anomalies;

        for(const auto& msg : copy)
        {
            if(msg.getTemperature() < minAllowed || msg.getTemperature() > maxAllowed)
            {
                anomalies.push_back(msg);
            }
        }

        return anomalies;
    }
}