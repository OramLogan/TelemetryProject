#include"core/TelemetryMessage.h"
#include"storage/InMemoryTelemetryStore.h"
#include"analysis/TelemetryAnalyzer.h"
#include"pipeline/TelemetryPipeline.h"
#include"analysis/TelemetryReportGenerator.h"
#include"logger/TelemetryLogger.h"
#include"api/TelemetryRoutes.h"
#include<iostream>
#include<vector>

#include<crow.h>



int main()
{
    telementary::TelemetryLogger appLogger("logs/AppErrors.log");

    try
    {
        telementary::TelemetryPipeline pipeline(4, 2, 4000);
        pipeline.start();

        telementary::TelemetryAnalyzer analyzer(pipeline.getInMemoryStore());
        telementary::TelemetryReportGenerator generator(analyzer);

        crow::SimpleApp app;

        telementary::TelemetryRoutes routes(app, pipeline, generator);
        routes.registerRoutes();

        app.port(8080).multithreaded().run();

        pipeline.stop();
        pipeline.wait();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Application startup failed: " << e.what() << std::endl;
        appLogger.logError(std::string("Startup error --> ") + e.what());
        return 1;
    }

    return 0;
}