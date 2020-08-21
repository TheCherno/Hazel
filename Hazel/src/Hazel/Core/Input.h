#pragma once

#include "Hazel/Core/Base.h"
#include "Hazel/Core/KeyCodes.h"
#include "Hazel/Core/MouseCodes.h"

namespace Hazel
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsKeyDown(KeyCode key);
		static bool IsKeyUp(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static bool IsMouseButtonDown(MouseCode button);
		static bool IsMouseButtonUp(MouseCode button);

		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();

	protected:
		static bool GetKey(KeyCode keycode);
		static bool GetMouseButton(MouseCode mousecode);

	private:
		friend class Application;

		static void OnUpdate();
	};
}
