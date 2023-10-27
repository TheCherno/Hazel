#pragma once

namespace Hazel
{
	const uint32_t MaxGamepadCount = 4;

	using GamepadCode = uint16_t;

	namespace Gamepad
	{
		enum : GamepadCode
		{
			DPadUp,
			DPadDown,
			DPadLeft,
			DPadRight,
			Start,
			Select,
			Back = Select,
			A,
			B,
			X,
			Y,
			Cross = B,
			Square = Y,
			Circle = A,
			Triangle = X,
			LeftThumb,
			RightThumb,
			LeftShoulder,
			RightShoulder
		};
	}
}
