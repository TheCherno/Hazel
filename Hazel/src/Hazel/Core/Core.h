#pragma once

#include <memory>

// Platform detection using predefined macros
#if defined HZ_PLATFORM_WINDOWS
	#ifndef _WIN64
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define HZ_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define HZ_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
/* We also have to check __ANDROID__ before __linux__
 * since android is based on the linux kernel
 * it has __linux__ defined */
#elif defined(__ANDROID__)
	#define HZ_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined HZ_PLATFORM_LINUX
#else
	/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif

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
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}
