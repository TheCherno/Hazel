#include "hzpch.h"
#include "Hazel/Core/Input.h"

#if defined(HZ_PLATFORM_WINDOWS)
	#include "Platform/Windows/WindowsInput.h"
#elif defined(HZ_PLATFORM_LINUX)
	#include "Platform/Windows/WindowsInput.h"
#endif

namespace Hazel {

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
	#if defined(HZ_PLATFORM_WINDOWS)
		return CreateScope<WindowsInput>();
	#elif defined(HZ_PLATFORM_LINUX)
		// Log is uninitialized here!
		//HZ_CORE_WARN("Hazel for Linux currently uses Hazel::WindowsInput!");
		return CreateScope<WindowsInput>();
	#else
		HZ_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}
} 