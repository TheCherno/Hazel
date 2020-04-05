#pragma once

namespace Hazel
{
	typedef enum class MouseCode : uint16_t
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
	} Mouse;
	
	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define HZ_MOUSE_BUTTON_0      ::Hazel::Mouse::Button0
#define HZ_MOUSE_BUTTON_1      ::Hazel::Mouse::Button1
#define HZ_MOUSE_BUTTON_2      ::Hazel::Mouse::Button2
#define HZ_MOUSE_BUTTON_3      ::Hazel::Mouse::Button3
#define HZ_MOUSE_BUTTON_4      ::Hazel::Mouse::Button4
#define HZ_MOUSE_BUTTON_5      ::Hazel::Mouse::Button5
#define HZ_MOUSE_BUTTON_6      ::Hazel::Mouse::Button6
#define HZ_MOUSE_BUTTON_7      ::Hazel::Mouse::Button7
#define HZ_MOUSE_BUTTON_LAST   ::Hazel::Mouse::ButtonLast
#define HZ_MOUSE_BUTTON_LEFT   ::Hazel::Mouse::ButtonLeft
#define HZ_MOUSE_BUTTON_RIGHT  ::Hazel::Mouse::ButtonRight
#define HZ_MOUSE_BUTTON_MIDDLE ::Hazel::Mouse::ButtonMiddle
