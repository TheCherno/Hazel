#pragma once

#include "Hazel/Core/Core.h"

namespace Hazel {

	class Input
	{
	protected:
		Input() = default;
	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

		inline static uint16_t GetKeyRepeatCount(int keycode) { return s_KeyRepeatCounts.count(keycode) == 0 ? 0 : s_KeyRepeatCounts[keycode]; }
		inline static uint16_t IncrementKeyRepeatCount(int keycode) { return s_KeyRepeatCounts[keycode]++; }
		inline static void ResetKeyRepeatCount(int keycode) { s_KeyRepeatCounts.erase(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Scope<Input> s_Instance;
		static std::unordered_map<uint16_t, unsigned int> s_KeyRepeatCounts;
	};
}