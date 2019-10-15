#pragma once

#include "Hazel/Core/Input.h"

namespace Hazel {

	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int32_t keycode) override;

		virtual bool IsMouseButtonPressedImpl(int32_t button) override;
		virtual std::pair<float_t, float_t> GetMousePositionImpl() override;
		virtual float_t GetMouseXImpl() override;
		virtual float_t GetMouseYImpl() override;
	};

}
