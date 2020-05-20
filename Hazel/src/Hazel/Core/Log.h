#pragma once

#include "Hazel/Core/Base.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Hazel {

	class Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}

#ifdef HZ_CORE_LIB
	#define HZ_LOG_TRACE(...)		::Hazel::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define HZ_LOG_DEBUG(...)		::Hazel::Log::GetCoreLogger()->debug(__VA_ARGS__)
	#define HZ_LOG_INFO(...)		::Hazel::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define HZ_LOG_WARN(...)		::Hazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define HZ_LOG_ERROR(...)		::Hazel::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define HZ_LOG_CRITICAL(...)	::Hazel::Log::GetCoreLogger()->critical(__VA_ARGS__)
#else
	#define HZ_LOG_TRACE(...)		::Hazel::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define HZ_LOG_DEBUG(...)		::Hazel::Log::GetClientLogger()->debug(__VA_ARGS__)
	#define HZ_LOG_INFO(...)		::Hazel::Log::GetClientLogger()->info(__VA_ARGS__)
	#define HZ_LOG_WARN(...)		::Hazel::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define HZ_LOG_ERROR(...)		::Hazel::Log::GetClientLogger()->error(__VA_ARGS__)
	#define HZ_LOG_CRITICAL(...)	::Hazel::Log::GetClientLogger()->critical(__VA_ARGS__)
#endif

#ifndef HZ_DEBUG
	#define HZ_LOG_TRACE(...) 
	#define HZ_LOG_DEBUG(...) 
#endif