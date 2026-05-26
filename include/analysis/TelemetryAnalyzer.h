#ifndef TELEMETRYANALYZER_H
#define TELEMETRYANALYZER_H

#include"core/ITelemetryStore.h"

#include<vector>
#include<string>

namespace telementary
{
    class TelemetryAnalyzer
    {
        private:
            const ITelemetryStore& _store;

        public:
          explicit TelemetryAnalyzer(const ITelemetryStore& store);

          double averageTemperature() const;
          double minTemperature() const;
          double maxTemperature() const;

          std::vector<TelemetryMessage> filterBySatelliteId(const std::string& satelliteId) const;
          std::vector<TelemetryMessage> detectAnomaly(double minAllowed, double maxAllowed) const;
    };
}

#endif