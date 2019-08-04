#include "hzpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "ImGui/ImGuiLogSink.h"

namespace Hazel {

    std::vector<spdlog::sink_ptr> Log::s_Sinks;
    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
        // create the sinks
        s_Sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>()); // VS debug console
        s_Sinks.emplace_back(std::make_shared<ImGuiLogSink_mt>()); // ImGuiConsole

        // create the loggers
        s_CoreLogger = std::make_shared<spdlog::logger>("HAZEL", begin(s_Sinks), end(s_Sinks));
        spdlog::register_logger(s_CoreLogger);
        s_ClientLogger = std::make_shared<spdlog::logger>("APP", begin(s_Sinks), end(s_Sinks));
        spdlog::register_logger(s_ClientLogger);

        // configure the loggers
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_CoreLogger->set_level(spdlog::level::trace);
        s_ClientLogger->set_level(spdlog::level::trace);

        // For testing purpose only
        s_CoreLogger->trace("This is a trace message.");
        s_CoreLogger->debug("This is a debug message.");
        s_CoreLogger->info("This is an info message.");
        s_CoreLogger->warn("This is a warning message.");
        s_CoreLogger->error("This is an error message.");
        s_CoreLogger->critical("This is a critical message.");

        s_ClientLogger->trace("This is a trace message.");
        s_ClientLogger->debug("This is a debug message.");
        s_ClientLogger->info("This is an info message.");
        s_ClientLogger->warn("This is a warning message.");
        s_ClientLogger->error("This is an error message.");
        s_ClientLogger->critical("This is a critical message.");
    }

}