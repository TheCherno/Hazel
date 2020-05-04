#pragma once

#include "Hazel/Core/Input.h"

namespace Hazel {

	class WindowsInput : public Input
	{
	protected:
		[[nodiscard]] bool IsKeyPressedImpl(KeyCode key) const override;

        [[nodiscard]] bool IsMouseButtonPressedImpl(MouseCode button) const override;
        [[nodiscard]] std::pair<float, float> GetMousePositionImpl() const override;
        [[nodiscard]] float GetMouseXImpl() const override;
        [[nodiscard]] float GetMouseYImpl() const override;
	};

}
