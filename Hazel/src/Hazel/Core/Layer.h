#pragma once

#include <string_view>
#include "Hazel/Core/Core.h"
#include "Hazel/Core/Timestep.h"
#include "Hazel/Events/Event.h"

namespace Hazel {

	class Layer
	{
	public:
		explicit Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(const Timestep& ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

        [[nodiscard]] std::string_view GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}