#include "hzpch.h"
//#include "Hazel/Core/Log.h"		included in hzpch.h already

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Hazel {

	Ref<spdlog::logger> Log::s_CoreLogger;
	Ref<spdlog::logger> Log::s_ClientLogger;


	void Log::Init()
	{
		// create the sinks
		std::vector<spdlog::sink_ptr> coreSinks;
		coreSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>()); // VS debug console
		coreSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Hazel-Core.log", true)); // CORE file logger

		std::vector<spdlog::sink_ptr> clientSinks;
		clientSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>()); // VS debug console
		clientSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Hazel-Client.log", true)); // CLIENT file logger

		// create the loggers
		s_CoreLogger = std::make_shared<spdlog::logger>("HAZEL", begin(coreSinks), end(coreSinks));
		spdlog::register_logger(s_CoreLogger);
		s_ClientLogger = std::make_shared<spdlog::logger>("APP", begin(clientSinks), end(clientSinks));
		spdlog::register_logger(s_ClientLogger);

		// configure the loggers
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger->set_level(spdlog::level::trace);
		s_ClientLogger->set_level(spdlog::level::trace);

	}

}

