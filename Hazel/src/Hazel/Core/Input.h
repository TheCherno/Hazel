#pragma once

#include "Hazel/Core/Core.h"
#include "Hazel/Core/KeyCodes.h"
#include "Hazel/Core/MouseButtonCodes.h"

#include "Hazel/Core/Log.h"

namespace Hazel {

	/* This struct holds a single input, either a key code or a mouse button code.
	 * Currently multiple alternative input is not supported.
	 */
	struct KeyAlternative
	{
		std::variant<Keys, MouseButtons> value;

		KeyAlternative() = default;
		KeyAlternative(Keys key) { value = key; }
		KeyAlternative(MouseButtons button) { value = button; }
	};

	class Input
	{
	protected:
		Input() = default;
	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		inline static bool IsInputPressed(const std::string& name)
		{
			if (s_Instance->m_Mapping.count(name) != 0)
				return IsInputPressed(s_Instance->m_Mapping[name]);

			HZ_CORE_WARN("The input {0} is not mapped!", name);
			return false;
		}

		inline static bool IsInputPressed(KeyAlternative input)
		{
			if (std::holds_alternative<Keys>(input.value))
				return s_Instance->IsKeyPressedImpl((int)std::get<Keys>(input.value));

			if (std::holds_alternative<MouseButtons>(input.value))
				return s_Instance->IsKeyPressedImpl((int)std::get<MouseButtons>(input.value));

			// control should never fall down here;
			HZ_CORE_WARN("Unknown Input type!");
			return false;
		}

		/* This function is still kept to ensure backward-compatibility. */
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsKeyPressed(Keys key) { return s_Instance->IsKeyPressedImpl((int)key); }
		/* This function is still kept to ensure backward-compatibility. */
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static bool IsMouseButtonPressed(MouseButtons button) { return s_Instance->IsMouseButtonPressedImpl((int)button); }

		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

		inline static void Remap(const std::string& name, KeyAlternative input) { s_Instance->m_Mapping[name] = input; }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		std::unordered_map<std::string, KeyAlternative> m_Mapping;

		static Scope<Input> s_Instance;
	};
}