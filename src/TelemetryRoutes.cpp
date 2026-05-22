#include"TelemetryRoutes.h"

namespace telementary
{
    TelemetryRoutes::TelemetryRoutes(crow::SimpleApp& app, TelemetryPipeline& pipeline, TelemetryReportGenerator& generator)
        : app(app), pipeline(pipeline), generator(generator) {}

    void TelemetryRoutes::registerRoutes()
    {
        registerHealthRoute();
        registerTelemetryRoutes();
        registerReportRoutes();
        registerLogRoute();
    }

    void TelemetryRoutes::registerHealthRoute()
    {
        CROW_ROUTE(app, "/")([]()
            {
                return "Routes Connected!!";
            });
    }

    void TelemetryRoutes::registerTelemetryRoutes()
    {
        CROW_ROUTE(app, "/telemetry/cache-count")([this]()
        {
            crow::json::wvalue response;
            response["cache_count"] = pipeline.getInMemoryStore().size();
            return crow::response(200, response);
        });

        CROW_ROUTE(app, "/telemetry/db-count")([this]()
        {
            try
            {
                crow::json::wvalue response;
                response["db_count"] = pipeline.getDatabaseStore().size();
                return crow::response(200, response);
            }
            catch (const std::exception& e)
            {
                return crow::response(500, e.what());
            }
        });

        CROW_ROUTE(app, "/telemetry/message").methods(crow::HTTPMethod::Post)([this](const crow::request& req)
        {
            auto body = crow::json::load(req.body);

            if(!body)
            {
                pipeline.makeLog("Invalid JSON");
                return crow::response(400, "Invalid JSON");
            }
            if(!body.has("satellite_id") || !body.has("timestamp") || !body.has("temperature"))
            {
                return crow::response(400, "Missing required fields");
            }

            try
            {
                std::string satelliteId = body["satellite_id"].s();
                int timestamp = body["timestamp"].i();
                double temperature = body["temperature"].d();

                telementary::TelemetryMessage msg(satelliteId, timestamp, temperature);

                if(!msg.isValid())
                {
                    pipeline.makeLog("Message Invalid", msg);
                    return crow::response(400, "Message Invalid");
                }

                pipeline.submitMessage(msg);

                return crow::response(202, "Message Processing");
            }
            catch(const std::exception& e)
            {
                return crow::response(400, e.what());
            }
        });
    }

    void TelemetryRoutes::registerReportRoutes()
    {
        CROW_ROUTE(app, "/telemetry/average-temperature")([this]()
        {
            try
            {
                auto report = generator.analysisReport().avgTemperature;
                crow::json::wvalue response;
                response["average_temperature"] = report;
                return crow::response(200, response);
            }
            catch(const std::exception& e)
            {
                return crow::response(400, e.what());
            }
        });

        CROW_ROUTE(app, "/telemetry/min-temperature")([this]()
        {
            try
            {
                auto report = generator.analysisReport().minTemperature;

                crow::json::wvalue response;
                response["min_temperature"] = report;
                return crow::response(200, response);
            }
            catch(const std::exception& e)
            {
                return crow::response(400, e.what());
            }
        });

        CROW_ROUTE(app, "/telemetry/max-temperature")([this]()
        {
            try
            {
                auto report = generator.analysisReport().maxTemperature;

                crow::json::wvalue response;
                response["max_temperature"] = report;
                return crow::response(200, response);
            }
            catch(const std::exception& e)
            {
                return crow::response(400, e.what());
            }
        });

        CROW_ROUTE(app, "/telemetry/report")([this]()
        {
            try
            {
                auto report = generator.analysisReport();

                crow::json::wvalue response;
                response["count"] = pipeline.getInMemoryStore().size();
                response["average_temperature"] = report.avgTemperature;
                response["min_temperature"] = report.minTemperature;
                response["max_temperature"] = report.maxTemperature;

                return crow::response(200, response);
            }
            catch(const std::exception& e)
            {
                return crow::response(400, e.what());
            }
        });
    }

    void TelemetryRoutes::registerLogRoute()
    {
        CROW_ROUTE(app, "/telemetry/error-log")([this]()
        {
            return crow::response(200, pipeline.readLog());
        });
    }
}