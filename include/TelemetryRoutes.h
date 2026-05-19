#ifndef TELEMETRYROUTES_H
#define TELEMETRYROUTES_H

#include"TelemetryPipeline.h"
#include"TelemetryAnalyzer.h"
#include"TelemetryReportGenerator.h"
#include"crow.h"

namespace telementary
{
    class TelemetryRoutes
    {
        public:
            TelemetryRoutes(crow::SimpleApp& app, TelemetryPipeline& pipeline, TelemetryReportGenerator& generator);
            void registerRoutes();

        private:
            crow::SimpleApp& app;
            TelemetryPipeline& pipeline;
            TelemetryReportGenerator& generator;

            void registerHealthRoute();
            void registerTelemetryRoutes();
            void registerReportRoutes();
            void registerLogRoute();
    };
}







#endif