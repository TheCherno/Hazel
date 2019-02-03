#pragma once

#if defined HZ_PLATFORM_WINDOWS
        #define HZ_DEBUG_BREAK { __debugbreak(); }
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API __declspec(dllexport)
	#else
		#define HAZEL_API __declspec(dllimport)
	#endif
#elif defined HZ_PLATFORM_LINUX
        #include <signal.h>
        #define HZ_DEBUG_BREAK { raise(SIGTRAP); }
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API __attribute__((visibility("default")))
	#else
		#define HAZEL_API
	#endif
#else
	#error Unsupported platform!
#endif

#ifdef HZ_DEBUG
	#define HZ_ENABLE_ASSERTS
#endif

#ifdef HZ_ENABLE_ASSERTS
	#define HZ_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); HZ_DEBUG_BREAK; } }
	#define HZ_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); HZ_DEBUG_BREAK; } }
#else
	#define HZ_ASSERT(x, ...)
	#define HZ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

