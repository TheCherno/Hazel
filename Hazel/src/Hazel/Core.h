#pragma once

#include <memory>

// Dynamic Link Library
#if defined HZ_PLATFORM_WINDOWS
	#if defined HZ_DYNAMIC_LINK
		#if defined HZ_BUILD_DLL
			#define HAZEL_API __declspec(dllexport)
		#else
			#define HAZEL_API __declspec(dllimport)
		#endif
	#else
		#define HAZEL_API
	#endif

#elif defined HZ_PLATFORM_LINUX
	#if defined HZ_DYNAMIC_LINK
		#if defined HZ_BUILD_DLL
			#define HAZEL_API __attribute__((visibility("default")))
		#else
			#define HAZEL_API
		#endif
	#else
		#define HAZEL_API
	#endif

#else
	#error Unsupported platform!
#endif // End of Dynamic Link Library

// Debug settings
#if defined HZ_DEBUG
	#if defined HZ_PLATFORM_WINDOWS
		#define HZ_DEBUGBREAK() __debugbreak()
	#elif defined HZ_PLATFORM_LINUX
		#include <signal.h>
		#define HZ_DEBUGBREAK() raise(SIGTRAP)
	#endif

	#define HZ_ENABLE_ASSERTS
#endif // End of Debug settings

// Assert statements
// HZ_ASSERT      will assert the passed statement; if not HZ_ENABLE_ASSERTS will do nothing
// HZ_ASSERT_CALL will assert the passed statement; if not HZ_ENABLE_ASSERTS will only call the statement
#if defined HZ_ENABLE_ASSERTS
	#define HZ_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); HZ_DEBUGBREAK(); } }
	#define HZ_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); HZ_DEBUGBREAK(); } }

	#define HZ_ASSERT_CALL(x, ...) HZ_ASSERT(x, __VA_ARGS__)
	#define HZ_CORE_ASSERT_CALL(x, ...) HZ_CORE_ASSERT(x, __VA_ARGS__)

#else
	#define HZ_ASSERT(x, ...)
	#define HZ_CORE_ASSERT(x, ...)

	#define HZ_ASSERT_CALL(x, ...) x
	#define HZ_CORE_ASSERT_CALL(x, ...) x
#endif // End of Assert statements

#define BIT(x) (1 << x)

#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Hazel {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}
