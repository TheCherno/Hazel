#pragma once

#include "Hazel/Core/Core.h"

namespace Hazel {

	class HAZEL_API Input
	{
	protected:
		Input() = default;
	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float_t, float_t> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float_t GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float_t GetMouseY() { return s_Instance->GetMouseYImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float_t, float_t> GetMousePositionImpl() = 0;
		virtual float_t GetMouseXImpl() = 0;
		virtual float_t GetMouseYImpl() = 0;
	private:
		static Scope<Input> s_Instance;
	};
}