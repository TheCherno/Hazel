#pragma once

#include "Hazel/Core/Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Hazel {

	class Log
	{
	public:
		static void Init();

		#ifdef HZ_DEBUG
			inline static Ref<spdlog::logger>& GetCoreDebugLogger() { return s_CoreDebugLogger; }
			inline static Ref<spdlog::logger>& GetClientDebugLogger() { return s_ClientDebugLogger; }
		#endif // HZ_DEBUG

		inline static Ref<spdlog::logger>& GetCoreFileLogger() { return s_CoreFileLogger; }
		inline static Ref<spdlog::logger>& GetClientFileLogger()	{ return s_ClientFileLogger; }

	private:
		#ifdef HZ_DEBUG
			static Ref<spdlog::logger> s_CoreDebugLogger;
			static Ref<spdlog::logger> s_ClientDebugLogger;
		#endif // HZ_DEBUG

		static Ref<spdlog::logger> s_CoreFileLogger;
		static Ref<spdlog::logger> s_ClientFileLogger;
	};

}

#pragma region Core Log Macros
#ifdef HZ_DEBUG
#define HZ_CORE_TRACE(...)										\
			Hazel::Log::GetCoreFileLogger()->trace(__VA_ARGS__);\
			Hazel::Log::GetCoreFileLogger()->flush();			\
			Hazel::Log::GetCoreDebugLogger()->trace(__VA_ARGS__)
#define HZ_CORE_INFO(...)										\
			Hazel::Log::GetCoreFileLogger()->info(__VA_ARGS__);	\
			Hazel::Log::GetCoreFileLogger()->flush();			\
			Hazel::Log::GetCoreDebugLogger()->info(__VA_ARGS__)
#define HZ_CORE_WARN(...)												\
			Hazel::Log::GetCoreFileLogger()->warn("\n*** Warning ***");	\
			Hazel::Log::GetCoreFileLogger()->warn(__VA_ARGS__);			\
			Hazel::Log::GetCoreFileLogger()->warn("");					\
			Hazel::Log::GetCoreFileLogger()->flush();					\
			Hazel::Log::GetCoreDebugLogger()->warn(__VA_ARGS__)
#define HZ_CORE_ERROR(...)												\
			Hazel::Log::GetCoreFileLogger()->error("\n*** Error ***");	\
			Hazel::Log::GetCoreFileLogger()->error(__VA_ARGS__);		\
			Hazel::Log::GetCoreFileLogger()->error("");					\
			Hazel::Log::GetCoreFileLogger()->flush();					\
			Hazel::Log::GetCoreDebugLogger()->error(__VA_ARGS__)
#define HZ_CORE_CRITICAL(...)												\
			Hazel::Log::GetCoreFileLogger()->critical("\n*** Critical ***");\
			Hazel::Log::GetCoreFileLogger()->critical(__VA_ARGS__);			\
			Hazel::Log::GetCoreFileLogger()->critical("");					\
			Hazel::Log::GetCoreFileLogger()->flush();						\
			Hazel::Log::GetCoreDebugLogger()->critical(__VA_ARGS__)
#elif HZ_RELEASE
#define HZ_CORE_TRACE(...)										\
			Hazel::Log::GetCoreFileLogger()->trace(__VA_ARGS__);\
			Hazel::Log::GetCoreFileLogger()->flush()
#define HZ_CORE_INFO(...)										\
			Hazel::Log::GetCoreFileLogger()->info(__VA_ARGS__);	\
			Hazel::Log::GetCoreFileLogger()->flush()
#define HZ_CORE_WARN(...)												\
			Hazel::Log::GetCoreFileLogger()->warn("\n*** Warning ***");	\
			Hazel::Log::GetCoreFileLogger()->warn(__VA_ARGS__);			\
			Hazel::Log::GetCoreFileLogger()->warn("");					\
			Hazel::Log::GetCoreFileLogger()->flush()						
#define HZ_CORE_ERROR(...)												\
			Hazel::Log::GetCoreFileLogger()->error("\n*** Error ***");	\
			Hazel::Log::GetCoreFileLogger()->error(__VA_ARGS__);		\
			Hazel::Log::GetCoreFileLogger()->error("");					\
			Hazel::Log::GetCoreFileLogger()->flush()
#define HZ_CORE_CRITICAL(...)												\
			Hazel::Log::GetCoreFileLogger()->critical("\n*** Critical ***");\
			Hazel::Log::GetCoreFileLogger()->critical(__VA_ARGS__);			\
			Hazel::Log::GetCoreFileLogger()->critical("");					\
			Hazel::Log::GetCoreFileLogger()->flush()
#endif
#pragma endregion

#pragma region Client Log Macros
#ifdef HZ_DEBUG
#define HZ_TRACE(...)												\
			Hazel::Log::GetClientFileLogger()->trace(__VA_ARGS__);	\
			Hazel::Log::GetClientFileLogger()->flush();				\
			Hazel::Log::GetClientDebugLogger()->trace(__VA_ARGS__)
#define HZ_INFO(...)												\
			Hazel::Log::GetClientFileLogger()->info(__VA_ARGS__);	\
			Hazel::Log::GetClientFileLogger()->flush();			\
			Hazel::Log::GetClientDebugLogger()->info(__VA_ARGS__)
#define HZ_WARN(...)														\
			Hazel::Log::GetClientFileLogger()->warn("\n*** Warning ***");	\
			Hazel::Log::GetClientFileLogger()->warn(__VA_ARGS__);			\
			Hazel::Log::GetClientFileLogger()->warn("");					\
			Hazel::Log::GetClientFileLogger()->flush();						\
			Hazel::Log::GetClientDebugLogger()->warn(__VA_ARGS__)
#define HZ_ERROR(...)													\
			Hazel::Log::GetClientFileLogger()->error("\n*** Error ***");\
			Hazel::Log::GetClientFileLogger()->error(__VA_ARGS__);		\
			Hazel::Log::GetClientFileLogger()->error("");				\
			Hazel::Log::GetClientFileLogger()->flush();					\
			Hazel::Log::GetClientDebugLogger()->error(__VA_ARGS__)
#define HZ_CRITICAL(...)														\
			Hazel::Log::GetClientFileLogger()->critical("\n*** Critical ***");	\
			Hazel::Log::GetClientFileLogger()->critical(__VA_ARGS__);			\
			Hazel::Log::GetClientFileLogger()->critical("");					\
			Hazel::Log::GetClientFileLogger()->flush();							\
			Hazel::Log::GetClientDebugLogger()->critical(__VA_ARGS__)
#elif HZ_RELEASE
#define HZ_TRACE(...)												\
			Hazel::Log::GetClientFileLogger()->trace(__VA_ARGS__);	\
			Hazel::Log::GetClientFileLogger()->flush()
#define HZ_INFO(...)												\
			Hazel::Log::GetClientFileLogger()->info(__VA_ARGS__);	\
			Hazel::Log::GetClientFileLogger()->flush()
#define HZ_WARN(...)														\
			Hazel::Log::GetClientFileLogger()->warn("\n*** Warning ***");	\
			Hazel::Log::GetClientFileLogger()->warn(__VA_ARGS__);			\
			Hazel::Log::GetClientFileLogger()->warn("");					\
			Hazel::Log::GetClientFileLogger()->flush()						
#define HZ_ERROR(...)													\
			Hazel::Log::GetClientFileLogger()->error("\n*** Error ***");\
			Hazel::Log::GetClientFileLogger()->error(__VA_ARGS__);		\
			Hazel::Log::GetClientFileLogger()->error("");				\
			Hazel::Log::GetClientFileLogger()->flush()
#define HZ_CRITICAL(...)														\
			Hazel::Log::GetClientFileLogger()->critical("\n*** Critical ***");	\
			Hazel::Log::GetClientFileLogger()->critical(__VA_ARGS__);			\
			Hazel::Log::GetClientFileLogger()->critical("");					\
			Hazel::Log::GetClientFileLogger()->flush()
#endif
#pragma endregion

