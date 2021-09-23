#include "hzpch.h"
#include "Hazel/Core/Window.h"

#if defined(HZ_PLATFORM_WINDOWS) || defined(HZ_PLATFORM_LINUX)
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Hazel
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
	#if defined(HZ_PLATFORM_WINDOWS) || defined(HZ_PLATFORM_LINUX)
		return CreateScope<WindowsWindow>(props);
	#else
		HZ_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}

}
