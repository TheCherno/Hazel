#include "hzpch.h"
#include "Hazel/Core/Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Hazel {

	Ref<spdlog::logger> Log::s_CoreLogger;
	Ref<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());// s_ConsoleSink);
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Hazel.log", true));

		s_CoreLogger = std::make_shared<spdlog::logger>("ENGINE", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_CoreLogger);
		s_ClientLogger = std::make_shared<spdlog::logger>("CLIENT", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_ClientLogger);

		s_CoreLogger->sinks()[0]->set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger->sinks()[1]->set_pattern("%n %L: %v");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger->sinks()[0]->set_pattern("%^[%T] %n: %v%$");
		s_ClientLogger->sinks()[1]->set_pattern("%n %L: %v");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

}

