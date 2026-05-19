#include"TelemetryMessage.h"
#include<sstream>
#include<stdexcept>

namespace telementary
{
    TelemetryMessage::TelemetryMessage()
        : _satelliteId("")
        , _timestamp(0)
        , _temperature(0.00)
    {}

    TelemetryMessage::TelemetryMessage(const std::string& satelliteId, std::int64_t timestamp, double temperature)
        : _satelliteId(satelliteId)
        , _timestamp(timestamp)
        , _temperature(temperature)
    {}

    const std::string& TelemetryMessage::getSatelliteId() const
    {
        return _satelliteId;
    }

    std::int64_t TelemetryMessage::getTimeStamp() const
    {
        return _timestamp;
    }

    double TelemetryMessage::getTemperature() const
    {
        return _temperature;
    }

    void TelemetryMessage::setSatelliteId(const std::string& satelliteId)
    {
        _satelliteId = satelliteId;
    }

    void TelemetryMessage::setTime(std::int64_t timestamp)
    {
        _timestamp = timestamp;
    }

    void TelemetryMessage::setTemperature(double temperature)
    {
        if(_temperature < -20000 || _temperature > 20000)
        {
            throw std::invalid_argument("Temperature out of range");
        }
        _temperature = temperature;
    }

    bool TelemetryMessage::isValid() const
    {
        if(!_satelliteId.empty() && _timestamp > 0 && (_temperature >= -20000 && _temperature <= 20000))
        {
            return true;
        }
        return false;
    }

    std::string TelemetryMessage::toString() const
    {
        std::ostringstream ss;
        ss << "[Telemetry] " << _satelliteId << " Time: " << _timestamp << " Temperature: " << _temperature << " C";
        return ss.str();
    }
}