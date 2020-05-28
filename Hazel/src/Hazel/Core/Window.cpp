#include "hzpch.h"
#include "Hazel/Core/Window.h"

#include "Platform/Windows/WindowsWindow.h"

namespace Hazel
{

	Scope<Window> Window::Create(const WindowProps& props)
	{
		return CreateScope<WindowsWindow>(props);
	}

}