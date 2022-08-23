#pragma once

#include "Hazel/Events/Event.h"

namespace Hazel {

	class GamepadEvent : public Event
	{
	public:
		GamepadEvent(uint32_t gamepadIndex)
			: m_GamepadIndex(gamepadIndex) {}

		uint32_t GetGamepadIndex() { return m_GamepadIndex; }

		EVENT_CLASS_CATEGORY(EventCategoryGamepad)
	protected:
		uint32_t m_GamepadIndex;
	};

	class GamepadConnectedEvent : public GamepadEvent
	{
	public:
		GamepadConnectedEvent(uint32_t gamepadIndex)
			: GamepadEvent(gamepadIndex) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "GamepadConnectedEvent: Player Index = " << m_GamepadIndex;
			return ss.str();
		}

		EVENT_CLASS_TYPE(GamepadConnected)
	};

	class GamepadDisconnectedEvent : public GamepadEvent
	{
	public:
		GamepadDisconnectedEvent(uint32_t gamepadIndex)
			: GamepadEvent(gamepadIndex) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "GamepadDisconnectedEvent: Player Index = " << m_GamepadIndex;
			return ss.str();
		}

		EVENT_CLASS_TYPE(GamepadDisconnected)
	};

}
