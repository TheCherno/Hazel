#include "hzpch.h"
#include "Platform/Windows/WindowsInput.h"

#include "Hazel/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Hazel {

	bool WindowsInput::IsKeyPressedImpl(KeyCode key)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		key = Input::GetCrossLayoutKey(key);

		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	KeyCode WindowsInput::GetCrossLayoutKeyImpl(KeyCode key) {

		//Check if the key is concerned by keyboards layout (letters)
		if (key >= KeyCode::A && key <= KeyCode::Z) {
			const std::string keyName = glfwGetKeyName(int(key), glfwGetKeyScancode(int(key)));
			return Key(int(KeyCode::A) + (std::toupper(keyName[0]) - 'A')); //Way to ensure that no matter the code that Hazel uses, the keycode will be correct
		}

		return key;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(MouseCode button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto[x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto[x, y] = GetMousePositionImpl();
		return y;
	}

}