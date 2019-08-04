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

        // create the logger
        s_CoreLogger = std::make_shared<spdlog::logger>("HAZEL", begin(s_Sinks), end(s_Sinks));
        spdlog::register_logger(s_CoreLogger);
        s_CoreLogger->set_level(spdlog::level::trace);

        s_ClientLogger = std::make_shared<spdlog::logger>("APP", begin(s_Sinks), end(s_Sinks));
        spdlog::register_logger(s_ClientLogger);
        s_ClientLogger->set_level(spdlog::level::trace);

        spdlog::set_pattern("%^[%T] %n: %v%$");
	}

}