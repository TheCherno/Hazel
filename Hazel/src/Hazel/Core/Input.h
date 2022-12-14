#pragma once

#include "Hazel/Core/KeyCodes.h"
#include "Hazel/Core/MouseCodes.h"

#include <glm/glm.hpp>

namespace Hazel {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}
