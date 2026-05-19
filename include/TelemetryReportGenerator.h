#ifndef TELEMETRYREPORTGENERATOR_H
#define TELEMETRYREPORTGENERATOR_H

#include"TelemetryAnalyzer.h"

namespace telementary
{
    struct TelemetryAnalysisReport
    {
        double avgTemperature;
        double minTemperature;
        double maxTemperature;
        std::vector<TelemetryMessage> hasAnomaly;
    };

    class TelemetryReportGenerator
    {
        private:
            const TelemetryAnalyzer& analyzer;

        public:
            explicit TelemetryReportGenerator(const TelemetryAnalyzer& analyzer);
            TelemetryAnalysisReport analysisReport();
    };
}










#endif