#include "hzpch.h"
//#include "Hazel/Core/Log.h"		included in hzpch.h already

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Hazel {

	#ifdef HZ_DEBUG
		Ref<spdlog::logger> Log::s_CoreDebugLogger;
		Ref<spdlog::logger> Log::s_ClientDebugLogger;
	#endif // HZ_DEBUG

	Ref<spdlog::logger> Log::s_CoreFileLogger;
	Ref<spdlog::logger> Log::s_ClientFileLogger;

	void Log::Init()
	{
		#ifdef HZ_DEBUG
			s_CoreDebugLogger = spdlog::stdout_color_mt("HAZEL");
			HZ_ASSERT(s_CoreDebugLogger, "Could not initialize Core Debug Logger!");
			s_CoreDebugLogger->set_pattern("%^[%T]: %v%$");
			s_CoreDebugLogger->set_level(spdlog::level::trace);

			s_ClientDebugLogger = spdlog::stdout_color_mt("APP");
			HZ_ASSERT(s_ClientDebugLogger, "Could not initialize App Debug Logger!");
			s_ClientDebugLogger->set_pattern("%^[%T]: %v%$");
			s_ClientDebugLogger->set_level(spdlog::level::trace);
		#endif // HZ_DEBUG

		s_CoreFileLogger = spdlog::basic_logger_mt("HAZEL-FILE", "hazel-log.txt", true);
		HZ_ASSERT(s_CoreFileLogger, "Could not initialize Core File Logger!");
		s_CoreFileLogger->set_pattern("%v");
		s_CoreFileLogger->set_level(spdlog::level::trace);

		s_ClientFileLogger = spdlog::basic_logger_mt("CLIENT-FILE", "client-log.txt", true);
		HZ_ASSERT(s_ClientFileLogger, "Could not initialize Client File Logger!");
		s_ClientFileLogger->set_pattern("%v");
		s_ClientFileLogger->set_level(spdlog::level::trace);
	}

}

