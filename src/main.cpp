#include"TelemetryMessage.h"
#include"InMemoryTelemetryStore.h"
#include"TelemetryAnalyzer.h"
#include"TelemetryQueue.h"
#include"TelemetryProcessor.h"
#include"TelemetryProducer.h"
#include"TelemetryPipeline.h"
#include"TelemetryReportGenerator.h"
#include"TelemetryRoutes.h"
#include"TelemetryLogger.h"
#include<iostream>
#include<thread>
#include<vector>
#include<future>

#include"crow.h"



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
        appLogger.logError(std::string("Startup error --> ") + e.what());
        return 1;
    }

    return 0;
}