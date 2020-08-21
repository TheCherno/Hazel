#include "hzpch.h"
#include "Hazel/Core/Input.h"

#include "Hazel/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Hazel {
	static std::unordered_map<KeyCode, bool> s_KeyStateMap(0);
	static std::unordered_map<MouseCode, bool> s_MouseButtonStateMap(0);

	static std::vector<KeyCode> s_AllKeys =
	{
		KeyCode::Space,
		KeyCode::Apostrophe,
		KeyCode::Comma,
		KeyCode::Minus,
		KeyCode::Period,
		KeyCode::Slash,
		KeyCode::D0,
		KeyCode::D1,
		KeyCode::D2,
		KeyCode::D3,
		KeyCode::D4,
		KeyCode::D5,
		KeyCode::D6,
		KeyCode::D7,
		KeyCode::D8,
		KeyCode::D9,
		KeyCode::Semicolon,
		KeyCode::Equal,
		KeyCode::A,
		KeyCode::B,
		KeyCode::C,
		KeyCode::D,
		KeyCode::E,
		KeyCode::F,
		KeyCode::G,
		KeyCode::H,
		KeyCode::I,
		KeyCode::J,
		KeyCode::K,
		KeyCode::L,
		KeyCode::M,
		KeyCode::N,
		KeyCode::O,
		KeyCode::P,
		KeyCode::Q,
		KeyCode::R,
		KeyCode::S,
		KeyCode::T,
		KeyCode::U,
		KeyCode::V,
		KeyCode::W,
		KeyCode::X,
		KeyCode::Y,
		KeyCode::Z,
		KeyCode::LeftBracket,
		KeyCode::Backslash,
		KeyCode::RightBracket,
		KeyCode::GraveAccent,
		KeyCode::World1,
		KeyCode::World2,
		KeyCode::Escape,
		KeyCode::Enter,
		KeyCode::Tab,
		KeyCode::Backspace,
		KeyCode::Insert,
		KeyCode::Delete,
		KeyCode::Right,
		KeyCode::Left,
		KeyCode::Down,
		KeyCode::Up,
		KeyCode::PageUp,
		KeyCode::PageDown,
		KeyCode::Home,
		KeyCode::End,
		KeyCode::CapsLock,
		KeyCode::ScrollLock,
		KeyCode::NumLock,
		KeyCode::PrintScreen,
		KeyCode::Pause,
		KeyCode::F1,
		KeyCode::F2,
		KeyCode::F3,
		KeyCode::F4,
		KeyCode::F5,
		KeyCode::F6,
		KeyCode::F7,
		KeyCode::F8,
		KeyCode::F9,
		KeyCode::F10,
		KeyCode::F11,
		KeyCode::F12,
		KeyCode::F13,
		KeyCode::F14,
		KeyCode::F15,
		KeyCode::F16,
		KeyCode::F17,
		KeyCode::F18,
		KeyCode::F19,
		KeyCode::F20,
		KeyCode::F21,
		KeyCode::F22,
		KeyCode::F23,
		KeyCode::F24,
		KeyCode::F25,
		KeyCode::KP0,
		KeyCode::KP1,
		KeyCode::KP2,
		KeyCode::KP3,
		KeyCode::KP4,
		KeyCode::KP5,
		KeyCode::KP6,
		KeyCode::KP7,
		KeyCode::KP8,
		KeyCode::KP9,
		KeyCode::KPDecimal,
		KeyCode::KPDivide,
		KeyCode::KPMultiply,
		KeyCode::KPSubtract,
		KeyCode::KPAdd,
		KeyCode::KPEnter,
		KeyCode::KPEqual,
		KeyCode::LeftShift,
		KeyCode::LeftControl,
		KeyCode::LeftAlt,
		KeyCode::LeftSuper,
		KeyCode::RightShift,
		KeyCode::RightControl,
		KeyCode::RightAlt,
		KeyCode::RightSuper,
		KeyCode::Menu
	};

	static std::vector<MouseCode> s_AllMouseButtons =
	{
		MouseCode::Button0,
		MouseCode::Button1,
		MouseCode::Button2,
		MouseCode::Button3,
		MouseCode::Button4,
		MouseCode::Button5,
		MouseCode::Button6,
		MouseCode::Button7
	};

	bool Input::IsKeyPressed(KeyCode key)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsKeyDown(KeyCode key)
	{
		return GetKey(key) && !s_KeyStateMap[key];
	}

	bool Input::IsKeyUp(KeyCode key)
	{
		return !GetKey(key) && s_KeyStateMap[key];
	}

	bool Input::IsMouseButtonPressed(MouseCode button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	bool Input::IsMouseButtonDown(MouseCode button)
	{
		return GetMouseButton(button) && !s_MouseButtonStateMap[button];
	}

	bool Input::IsMouseButtonUp(MouseCode button)
	{
		return !GetMouseButton(button) && s_MouseButtonStateMap[button];
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float Input::GetMouseX()
	{
		auto [x, y] = GetMousePosition();
		return x;
	}

	float Input::GetMouseY()
	{
		auto [x, y] = GetMousePosition();
		return y;
	}

	bool Input::GetKey(KeyCode keycode)
	{
		return glfwGetKey(static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()),
			static_cast<int32_t>(keycode)) == GLFW_PRESS;
	}

	bool Input::GetMouseButton(MouseCode mousecode)
	{
		return glfwGetMouseButton(static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()),
			static_cast<int32_t>(mousecode)) == GLFW_PRESS;
	}

	void Input::OnUpdate()
	{
		for (KeyCode key : s_AllKeys) {
			s_KeyStateMap[key] = GetKey(key);
		}

		for (MouseCode mouseButton : s_AllMouseButtons) {
			s_MouseButtonStateMap[mouseButton] = GetMouseButton(mouseButton);
		}
	}
}