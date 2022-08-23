#pragma once

#include "Hazel/Core/KeyCodes.h"
#include "Hazel/Core/MouseCodes.h"
#include "Hazel/Core/GamepadCodes.h"
#include "Hazel/Events/Event.h"

#include <glm/glm.hpp>

namespace Hazel {

	class Input
	{
	public:
		static void Init();
		static void SetEventCallback(const EventCallbackFn& callback);
		static void Update();

		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();

		static bool IsGamepadButtonPressed(uint32_t playerIndex, GamepadCode code);
		static bool IsGamepadButtonReleased(uint32_t playerIndex, GamepadCode code);
		static glm::vec2 GetGamepadLeftJoystick(uint32_t playerIndex);
		static glm::vec2 GetGamepadRightJoystick(uint32_t playerIndex);
		static glm::vec2 GetGamepadTriggers(uint32_t playerIndex);
		static void SetGamepadVibration(uint32_t playerIndex, const glm::vec2& vibration);
	};
}
