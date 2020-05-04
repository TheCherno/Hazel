#pragma once

#include "Hazel/Core/Core.h"
#include "Hazel/Core/KeyCodes.h"
#include "Hazel/Core/MouseCodes.h"

namespace Hazel {

	class Input
	{
	protected:
		Input() = default;
	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		static bool IsKeyPressed(KeyCode key) { return s_Instance->IsKeyPressedImpl(key); }

		static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

		static Scope<Input> Create();
	protected:
        [[nodiscard]] virtual bool IsKeyPressedImpl(KeyCode key) const = 0;

        [[nodiscard]] virtual bool IsMouseButtonPressedImpl(MouseCode button) const = 0;
        [[nodiscard]] virtual std::pair<float, float> GetMousePositionImpl() const = 0;
        [[nodiscard]] virtual float GetMouseXImpl() const = 0;
        [[nodiscard]] virtual float GetMouseYImpl() const = 0;
	private:
		static Scope<Input> s_Instance;
	};
}
