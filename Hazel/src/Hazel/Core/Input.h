#pragma once

#include "Hazel/Core/Core.h"
#include "Hazel/Core/KeyCodes.h"
#include "Hazel/Core/MouseCodes.h"

namespace Hazel {

	// TODO: If this enum class grows too big, we will move it to another .h file;
	/* Hold the name for an input to be mapped. */
	enum class InputName : uint16_t
	{
		CameraMoveLeft = 1,
		CameraMoveRight = 2,
		CameraMoveUp = 3,
		CameraMoveDown = 4,
		CameraRotateClockwise = 5,
		CameraRotateAntiClockwise = 6,
	};

	/* Holds a single input, either a KeyCode or a MouseCode. */
	struct InputKey
	{
		std::variant<KeyCode, MouseCode> value;

		InputKey() = default;
		InputKey(KeyCode key) { value = key; }
		InputKey(MouseCode button) { value = button; }
	};

	class Input
	{
	protected:
		Input() = default;
	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		template <typename T>
		static bool IsInputPressed(T name)
		{
			if (s_Instance->m_Mapping.count(static_cast<uint16_t>(name)) != 0)
				return IsInputPressed(s_Instance->m_Mapping[static_cast<uint16_t>(name)]);

			HZ_CORE_WARN("The input {0} is not mapped!", static_cast<uint16_t>(name));
			return false;
		}

		inline static bool IsInputPressed(InputKey inputKey)
		{
			if (std::holds_alternative<KeyCode>(inputKey.value))
				return s_Instance->IsKeyPressedImpl(std::get<KeyCode>(inputKey.value));

			if (std::holds_alternative<MouseCode>(inputKey.value))
				return s_Instance->IsMouseButtonPressedImpl(std::get<MouseCode>(inputKey.value));

			// control should never fall down here;
			HZ_CORE_WARN("Unknown Input type!");
			return false;
		}

		inline static bool IsKeyPressed(KeyCode key) { return s_Instance->IsKeyPressedImpl(key); }

		inline static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

		/* Map a Key/Mouse Button to an InputKey, and overwrite the old value if existed. */
		template <typename T>
		static void Remap(T name, InputKey inputKey) { s_Instance->m_Mapping[static_cast<uint16_t>(name)] = inputKey; }

		static Scope<Input> Create();
	protected:
		virtual bool IsKeyPressedImpl(KeyCode key) = 0;

		virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Scope<Input> s_Instance;
		std::unordered_map<uint16_t, InputKey> m_Mapping;
	};
}