#include "hzpch.h"
#include "Hazel/Core/Window.h"

#if defined(HZ_PLATFORM_WINDOWS)
	#include "Platform/Windows/WindowsWindow.h"
#elif defined(HZ_PLATFORM_LINUX)
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Hazel
{

	Scope<Window> Window::Create(const WindowProps& props)
	{
	#if defined(HZ_PLATFORM_WINDOWS)
		return CreateScope<WindowsWindow>(props);
	#elif defined(HZ_PLATFORM_LINUX)
		HZ_CORE_WARN("Hazel for Linux currently uses Hazel::WindowsWindow!"); // See Input::Create()
		return CreateScope<WindowsWindow>(props);
	#else
		HZ_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}

}