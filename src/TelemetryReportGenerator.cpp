#include"TelemetryReportGenerator.h"
#include<future>

namespace telementary
{
    TelemetryReportGenerator::TelemetryReportGenerator(const TelemetryAnalyzer& analyzer)
        : analyzer(analyzer) {}
    
    TelemetryAnalysisReport TelemetryReportGenerator::analysisReport()
    {
        auto avgFuture = std::async(std::launch::async, [this]()
        {
            return analyzer.averageTemperature();
        });

        auto minFuture = std::async(std::launch::async, [this]()
        {
            return analyzer.minTemperature();
        });

        auto maxFuture = std::async(std::launch::async, [this]()
        {
            return analyzer.maxTemperature();
        });

        auto anomalyFuture = std::async(std::launch::async, [this]()
        {
            return analyzer.detectAnomaly(-100, 1000);
        });

        TelemetryAnalysisReport report;

        report.avgTemperature = avgFuture.get();
        report.minTemperature = minFuture.get();
        report.maxTemperature = maxFuture.get();
        report.hasAnomaly = anomalyFuture.get();

        return report;
    }
}