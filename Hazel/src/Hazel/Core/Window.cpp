#include "hzpch.h"

#include "Window.h"

#ifdef HZ_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
	namespace Hazel {
		Scope<Window> Window::Create(const WindowProps& props)
		{
			return CreateScope<WindowsWindow>(props);
	}
}
#else
	#error "Only Windows supported!"
#endif 
