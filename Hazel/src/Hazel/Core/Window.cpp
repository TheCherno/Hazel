#include "hzpch.h"
#include "Hazel/Core/Window.h"

#if defined(HZ_PLATFORM_WINDOWS)
	#include "Platform/Windows/WindowsWindow.h"
#elif defined(HZ_PLATFORM_LINUX)
        #include "Platform/Linux/LinuxWindow.h"
#endif

namespace Hazel
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
	  HZ_CORE_TRACE("Window::Create");
        #if defined(HZ_PLATFORM_WINDOWS)
		return CreateScope<WindowsWindow>(props);
        #elif defined(HZ_PLATFORM_LINUX)
		return CreateScope<LinuxWindow>(props);
	#else
		HZ_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	#endif
	}

}
