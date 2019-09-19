#pragma once

namespace Hazel
{
	enum class MouseCode
	{
		// From glfw3.h
		Button0                = 0,
		Button1                = 1,
		Button2                = 2,
		Button3                = 3,
		Button4                = 4,
		Button5                = 5,
		Button6                = 6,
		Button7                = 7,
		ButtonLast             = Button7,
		ButtonLeft             = Button0,
		ButtonRight            = Button1,
		ButtonMiddle           = Button2

	};
}

#define HZ_MOUSE_BUTTON_0      ::Hazel::MouseCode::Button0
#define HZ_MOUSE_BUTTON_1      ::Hazel::MouseCode::Button1
#define HZ_MOUSE_BUTTON_2      ::Hazel::MouseCode::Button2
#define HZ_MOUSE_BUTTON_3      ::Hazel::MouseCode::Button3
#define HZ_MOUSE_BUTTON_4      ::Hazel::MouseCode::Button4
#define HZ_MOUSE_BUTTON_5      ::Hazel::MouseCode::Button5
#define HZ_MOUSE_BUTTON_6      ::Hazel::MouseCode::Button6
#define HZ_MOUSE_BUTTON_7      ::Hazel::MouseCode::Button7
#define HZ_MOUSE_BUTTON_LAST   ::Hazel::MouseCode::ButtonLast
#define HZ_MOUSE_BUTTON_LEFT   ::Hazel::MouseCode::ButtonLeft
#define HZ_MOUSE_BUTTON_RIGHT  ::Hazel::MouseCode::ButtonRight
#define HZ_MOUSE_BUTTON_MIDDLE ::Hazel::MouseCode::ButtonMiddle
