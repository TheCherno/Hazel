#include "hzpch.h"
#include "Hazel/Core/Input.h"

#include "Hazel/Core/Application.h"
#include <GLFW/glfw3.h>

#include "Hazel/Events/GamepadEvent.h"

#include <xinput.h>

// Define the layout of the function we're going to load. Make a default one in case we're unable to load it from the dll.
#define XINPUT_GET_STATE(name) DWORD name(DWORD dwUserIndex, XINPUT_STATE* pState)
typedef XINPUT_GET_STATE(xinput_get_state);
XINPUT_GET_STATE(XInputGetStateStub) { return ERROR_DEVICE_NOT_CONNECTED; }
static xinput_get_state* XInputGetState_ = XInputGetStateStub;
#define XInputGetState XInputGetState_

// Same here.
#define XINPUT_SET_STATE(name) DWORD name(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration)
typedef XINPUT_SET_STATE(xinput_set_state);
XINPUT_SET_STATE(XInputSetStateStub) { return ERROR_DEVICE_NOT_CONNECTED; }
static xinput_set_state* XInputSetState_ = XInputSetStateStub;
#define XInputSetState XInputSetState_


namespace Hazel {

	const float DeadzoneX = 0.05f;
	const float DeadzoneY = 0.02f;

	struct GamepadState
	{
		bool IsConnected;
		std::unordered_map<GamepadCode, bool> Buttons;
		glm::vec2 LeftJoystick;
		glm::vec2 RightJoystick;
		glm::vec2 Triggers;
		glm::vec2 Vibration;
	};

	static std::array<GamepadState, MaxGamepadCount> s_Gamepads;
	static EventCallbackFn s_EventCallback;

	void Input::Init()
	{
		HZ_PROFILE_FUNCTION();

		s_Gamepads = {};

		HMODULE Module = LoadLibraryA("xinput1_4.dll");
		if (!Module)
		{
			HZ_CORE_ERROR("Failed to load xinput1_4.dll!");
			return;
		}

		XInputGetState = (xinput_get_state*)GetProcAddress(Module, "XInputGetState");
		XInputSetState = (xinput_set_state*)GetProcAddress(Module, "XInputSetState");
	}

	void Input::SetEventCallback(const EventCallbackFn& callback)
	{
		s_EventCallback = callback;
	}

	void Input::Update()
	{
		HZ_PROFILE_FUNCTION();

		for (uint32_t i = 0; i < MaxGamepadCount; i++)
		{
			XINPUT_STATE state;
			ZeroMemory(&state, sizeof(XINPUT_STATE));

			DWORD result = XInputGetState(i, &state);
			bool connected = (result == ERROR_SUCCESS);

			if (s_Gamepads[i].IsConnected != connected)
			{
				if (connected == true)
				{
					GamepadConnectedEvent event(i);
					s_EventCallback(event);
				}
				else
				{
					GamepadDisconnectedEvent event(i);
					s_EventCallback(event);
				}
			}

			s_Gamepads[i].IsConnected = connected;
			if (connected)
			{
				// Diamond Buttons
				s_Gamepads[i].Buttons[Gamepad::A] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_A);
				s_Gamepads[i].Buttons[Gamepad::B] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_B);
				s_Gamepads[i].Buttons[Gamepad::X] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_X);
				s_Gamepads[i].Buttons[Gamepad::Y] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y);

				// DPad Buttons
				s_Gamepads[i].Buttons[Gamepad::DPadDown] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
				s_Gamepads[i].Buttons[Gamepad::DPadUp] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP);
				s_Gamepads[i].Buttons[Gamepad::DPadLeft] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
				s_Gamepads[i].Buttons[Gamepad::DPadRight] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);

				// Navigation buttons
				s_Gamepads[i].Buttons[Gamepad::Start] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_START);
				s_Gamepads[i].Buttons[Gamepad::Back] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK);

				// Shoulder buttons
				s_Gamepads[i].Buttons[Gamepad::LeftShoulder] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
				s_Gamepads[i].Buttons[Gamepad::RightShoulder] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);

				// Thumbstick buttons
				s_Gamepads[i].Buttons[Gamepad::LeftThumb] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB);
				s_Gamepads[i].Buttons[Gamepad::RightThumb] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB);

				// Triggers
				s_Gamepads[i].Triggers.x = (float)state.Gamepad.bLeftTrigger / 255;
				s_Gamepads[i].Triggers.y = (float)state.Gamepad.bRightTrigger / 255;

				// Left joystick
				float normLX = fmaxf(-1, (float)state.Gamepad.sThumbLX / 32767);
				float normLY = fmaxf(-1, (float)state.Gamepad.sThumbLY / 32767);

				s_Gamepads[i].LeftJoystick.x = (abs(normLX) < DeadzoneX ? 0 : (abs(normLX) - DeadzoneX) * (normLX / abs(normLX)));
				s_Gamepads[i].LeftJoystick.y = (abs(normLY) < DeadzoneY ? 0 : (abs(normLY) - DeadzoneY) * (normLY / abs(normLY)));
				s_Gamepads[i].LeftJoystick.x *= 1 / (1 - DeadzoneX);
				s_Gamepads[i].LeftJoystick.y *= 1 / (1 - DeadzoneY);

				// Right joystick
				float normRX = fmaxf(-1, (float)state.Gamepad.sThumbRX / 32767);
				float normRY = fmaxf(-1, (float)state.Gamepad.sThumbRY / 32767);

				s_Gamepads[i].RightJoystick.x = (abs(normRX) < DeadzoneX ? 0 : (abs(normRX) - DeadzoneX) * (normRX / abs(normRX)));
				s_Gamepads[i].RightJoystick.y = (abs(normRY) < DeadzoneY ? 0 : (abs(normRY) - DeadzoneY) * (normRY / abs(normRY)));
				s_Gamepads[i].RightJoystick.x *= 1 / (1 - DeadzoneX);
				s_Gamepads[i].RightJoystick.y *= 1 / (1 - DeadzoneY);

				// Set vibration
				XINPUT_VIBRATION vibration = {};
				vibration.wLeftMotorSpeed = (uint16_t)(s_Gamepads[i].Vibration.x * 65335.0f);
				vibration.wRightMotorSpeed = (uint16_t)(s_Gamepads[i].Vibration.y * 65335.0f);
				XInputSetState(i, &vibration);
				
				// Reset vibration
				s_Gamepads[i].Vibration = glm::vec2(0.0f);
			}
		}
	}

	bool Input::IsKeyPressed(const KeyCode key)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS;
	}

	bool Input::IsMouseButtonPressed(const MouseCode button)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePosition()
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float Input::GetMouseX()
	{
		return GetMousePosition().x;
	}

	float Input::GetMouseY()
	{
		return GetMousePosition().y;
	}

	bool Input::IsGamepadButtonPressed(uint32_t playerIndex, GamepadCode code)
	{
		return s_Gamepads[playerIndex].Buttons[code] == true;
	}

	bool Input::IsGamepadButtonReleased(uint32_t playerIndex, GamepadCode code)
	{
		return s_Gamepads[playerIndex].Buttons[code] == false;
	}

	glm::vec2 Input::GetGamepadLeftJoystick(uint32_t playerIndex)
	{
		return s_Gamepads[playerIndex].LeftJoystick;
	}

	glm::vec2 Input::GetGamepadRightJoystick(uint32_t playerIndex)
	{
		return s_Gamepads[playerIndex].RightJoystick;
	}

	glm::vec2 Input::GetGamepadTriggers(uint32_t playerIndex)
	{
		return s_Gamepads[playerIndex].Triggers;
	}

	void Input::SetGamepadVibration(uint32_t playerIndex, const glm::vec2& vibration)
	{
		s_Gamepads[playerIndex].Vibration = vibration;
	}
}
