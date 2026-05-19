#ifndef TELEMETRYMESSAGE_H
#define TELEMETRYMESSAGE_H

#include<string>
#include<cstdint>

namespace telementary
{

    class TelemetryMessage
    {

        private:
            std::string _satelliteId;
            std::int64_t _timestamp;
            double _temperature;

        public:
            TelemetryMessage();
            TelemetryMessage(const std::string&, std::int64_t, double);

            const std::string& getSatelliteId() const;
            std::int64_t getTimeStamp() const;
            double getTemperature() const;

            void setSatelliteId(const std::string&);
            void setTime(std::int64_t);
            void setTemperature(double);

            bool isValid() const;

            std::string toString() const;
    };
}

#endif