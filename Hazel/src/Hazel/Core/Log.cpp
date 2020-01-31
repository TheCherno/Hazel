#include "hzpch.h"
//#include "Hazel/Core/Log.h"		included in hzpch.h already

#include <spdlog/sinks/basic_file_sink.h>

namespace Hazel {

	Ref<spdlog::logger> Log::s_CoreLogger;
	Ref<spdlog::logger> Log::s_ClientLogger;
	Ref<spdlog::sinks::stdout_color_sink_mt> Log::s_ConsoleSink;

	void Log::Init()
	{
		s_ConsoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

		std::vector<spdlog::sink_ptr> coreSinks;
		coreSinks.emplace_back(s_ConsoleSink); // VS debug console
		coreSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Hazel-Core.log", true));

		std::vector<spdlog::sink_ptr> clientSinks;
		clientSinks.emplace_back(s_ConsoleSink); // VS debug console
		clientSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Hazel-Client.log", true));

		s_CoreLogger = std::make_shared<spdlog::logger>("HAZEL", begin(coreSinks), end(coreSinks));
		spdlog::register_logger(s_CoreLogger);
		s_ClientLogger = std::make_shared<spdlog::logger>("APP", begin(clientSinks), end(clientSinks));
		spdlog::register_logger(s_ClientLogger);

		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger->set_level(spdlog::level::trace);
		s_ClientLogger->set_level(spdlog::level::trace);

	}

}

