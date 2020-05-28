#include "hzpch.h"
#include "Hazel/Core/Input.h"

#include "Platform/Windows/WindowsInput.h"

namespace Hazel {

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
		return CreateScope<WindowsInput>();
	}
} 