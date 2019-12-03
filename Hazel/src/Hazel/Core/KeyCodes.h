#pragma once

namespace Hazel
{
	enum class KeyCode
	{
		// From glfw3.h
		KeySpace               = 32,
		KeyApostrophe          = 39, /* ' */
		KeyComma               = 44, /* , */
		KeyMinus               = 45, /* - */
		KeyPeriod              = 46, /* . */
		KeySlash               = 47, /* / */
		Key0                   = 48,
		Key1                   = 49,
		Key2                   = 50,
		Key3                   = 51,
		Key4                   = 52,
		Key5                   = 53,
		Key6                   = 54,
		Key7                   = 55,
		Key8                   = 56,
		Key9                   = 57,
		KeySemicolon           = 59, /* ; */
		KeyEqual               = 61, /* = */
		KeyA                   = 65,
		KeyB                   = 66,
		KeyC                   = 67,
		KeyD                   = 68,
		KeyE                   = 69,
		KeyF                   = 70,
		KeyG                   = 71,
		KeyH                   = 72,
		KeyI                   = 73,
		KeyJ                   = 74,
		KeyK                   = 75,
		KeyL                   = 76,
		KeyM                   = 77,
		KeyN                   = 78,
		KeyO                   = 79,
		KeyP                   = 80,
		KeyQ                   = 81,
		KeyR                   = 82,
		KeyS                   = 83,
		KeyT                   = 84,
		KeyU                   = 85,
		KeyV                   = 86,
		KeyW                   = 87,
		KeyX                   = 88,
		KeyY                   = 89,
		KeyZ                   = 90,
		KeyLeftBracket         = 91,  /* [ */
		KeyBackslash           = 92,  /* \ */
		KeyRightBracket        = 93,  /* ] */
		KeyGraveAccent         = 96,  /* ` */
		KeyWorld1              = 161, /* non-US #1 */
		KeyWorld2              = 162, /* non-US #2 */

		/* Function keys */
		KeyEscape              = 256,
		KeyEnter               = 257,
		KeyTab                 = 258,
		KeyBackspace           = 259,
		KeyInsert              = 260,
		KeyDelete              = 261,
		KeyRight               = 262,
		KeyLeft                = 263,
		KeyDown                = 264,
		KeyUp                  = 265,
		KeyPageUp              = 266,
		KeyPageDown            = 267,
		KeyHome                = 268,
		KeyEnd                 = 269,
		KeyCapsLock            = 280,
		KeyScrollLock          = 281,
		KeyNumLock             = 282,
		KeyPrintScreen         = 283,
		KeyPause               = 284,
		KeyF1                  = 290,
		KeyF2                  = 291,
		KeyF3                  = 292,
		KeyF4                  = 293,
		KeyF5                  = 294,
		KeyF6                  = 295,
		KeyF7                  = 296,
		KeyF8                  = 297,
		KeyF9                  = 298,
		KeyF10                 = 299,
		KeyF11                 = 300,
		KeyF12                 = 301,
		KeyF13                 = 302,
		KeyF14                 = 303,
		KeyF15                 = 304,
		KeyF16                 = 305,
		KeyF17                 = 306,
		KeyF18                 = 307,
		KeyF19                 = 308,
		KeyF20                 = 309,
		KeyF21                 = 310,
		KeyF22                 = 311,
		KeyF23                 = 312,
		KeyF24                 = 313,
		KeyF25                 = 314,
		KeyKP0                 = 320,
		KeyKP1                 = 321,
		KeyKP2                 = 322,
		KeyKP3                 = 323,
		KeyKP4                 = 324,
		KeyKP5                 = 325,
		KeyKP6                 = 326,
		KeyKP7                 = 327,
		KeyKP8                 = 328,
		KeyKP9                 = 329,
		KeyKPDecimal           = 330,
		KeyKPDivide            = 331,
		KeyKPMultiply          = 332,
		KeyKPSubtract          = 333,
		KeyKPAdd               = 334,
		KeyKPEnter             = 335,
		KeyKPEqual             = 336,
		KeyLeftShift           = 340,
		KeyLeftControl         = 341,
		KeyLeftAlt             = 342,
		KeyLeftSuper           = 343,
		KeyRightShift          = 344,
		KeyRightControl        = 345,
		KeyRightAlt            = 346,
		KeyRightSuper          = 347,
		KeyMenu                = 348
	};

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define HZ_KEY_SPACE           ::Hazel::KeyCode::KeySpace
#define HZ_KEY_APOSTROPHE      ::Hazel::KeyCode::KeyApostrophe    /* ' */
#define HZ_KEY_COMMA           ::Hazel::KeyCode::KeyComma         /* , */
#define HZ_KEY_MINUS           ::Hazel::KeyCode::KeyMinus         /* - */
#define HZ_KEY_PERIOD          ::Hazel::KeyCode::KeyPeriod        /* . */
#define HZ_KEY_SLASH           ::Hazel::KeyCode::KeySlash         /* / */
#define HZ_KEY_0               ::Hazel::KeyCode::Key0
#define HZ_KEY_1               ::Hazel::KeyCode::Key1
#define HZ_KEY_2               ::Hazel::KeyCode::Key2
#define HZ_KEY_3               ::Hazel::KeyCode::Key3
#define HZ_KEY_4               ::Hazel::KeyCode::Key4
#define HZ_KEY_5               ::Hazel::KeyCode::Key5
#define HZ_KEY_6               ::Hazel::KeyCode::Key6
#define HZ_KEY_7               ::Hazel::KeyCode::Key7
#define HZ_KEY_8               ::Hazel::KeyCode::Key8
#define HZ_KEY_9               ::Hazel::KeyCode::Key9
#define HZ_KEY_SEMICOLON       ::Hazel::KeyCode::KeySemicolon     /* ; */
#define HZ_KEY_EQUAL           ::Hazel::KeyCode::KeyEqual         /* = */
#define HZ_KEY_A               ::Hazel::KeyCode::KeyA
#define HZ_KEY_B               ::Hazel::KeyCode::KeyB
#define HZ_KEY_C               ::Hazel::KeyCode::KeyC
#define HZ_KEY_D               ::Hazel::KeyCode::KeyD
#define HZ_KEY_E               ::Hazel::KeyCode::KeyE
#define HZ_KEY_F               ::Hazel::KeyCode::KeyF
#define HZ_KEY_G               ::Hazel::KeyCode::KeyG
#define HZ_KEY_H               ::Hazel::KeyCode::KeyH
#define HZ_KEY_I               ::Hazel::KeyCode::KeyI
#define HZ_KEY_J               ::Hazel::KeyCode::KeyJ
#define HZ_KEY_K               ::Hazel::KeyCode::KeyK
#define HZ_KEY_L               ::Hazel::KeyCode::KeyL
#define HZ_KEY_M               ::Hazel::KeyCode::KeyM
#define HZ_KEY_N               ::Hazel::KeyCode::KeyN
#define HZ_KEY_O               ::Hazel::KeyCode::KeyO
#define HZ_KEY_P               ::Hazel::KeyCode::KeyP
#define HZ_KEY_Q               ::Hazel::KeyCode::KeyQ
#define HZ_KEY_R               ::Hazel::KeyCode::KeyR
#define HZ_KEY_S               ::Hazel::KeyCode::KeyS
#define HZ_KEY_T               ::Hazel::KeyCode::KeyT
#define HZ_KEY_U               ::Hazel::KeyCode::KeyU
#define HZ_KEY_V               ::Hazel::KeyCode::KeyV
#define HZ_KEY_W               ::Hazel::KeyCode::KeyW
#define HZ_KEY_X               ::Hazel::KeyCode::KeyX
#define HZ_KEY_Y               ::Hazel::KeyCode::KeyY
#define HZ_KEY_Z               ::Hazel::KeyCode::KeyZ
#define HZ_KEY_LEFT_BRACKET    ::Hazel::KeyCode::KeyLeftBracket   /* [ */
#define HZ_KEY_BACKSLASH       ::Hazel::KeyCode::KeyBackslash     /* \ */
#define HZ_KEY_RIGHT_BRACKET   ::Hazel::KeyCode::KeyRightBracket  /* ] */
#define HZ_KEY_GRAVE_ACCENT    ::Hazel::KeyCode::KeyGraveAccent   /* ` */
#define HZ_KEY_WORLD_1         ::Hazel::KeyCode::KeyWorld1        /* non-US #1 */
#define HZ_KEY_WORLD_2         ::Hazel::KeyCode::KeyWorld2        /* non-US #2 */

/* Function keys */
#define HZ_KEY_ESCAPE          ::Hazel::KeyCode::KeyEscape
#define HZ_KEY_ENTER           ::Hazel::KeyCode::KeyEnter
#define HZ_KEY_TAB             ::Hazel::KeyCode::KeyTab
#define HZ_KEY_BACKSPACE       ::Hazel::KeyCode::KeyBackspace
#define HZ_KEY_INSERT          ::Hazel::KeyCode::KeyInsert
#define HZ_KEY_DELETE          ::Hazel::KeyCode::KeyDelete
#define HZ_KEY_RIGHT           ::Hazel::KeyCode::KeyRight
#define HZ_KEY_LEFT            ::Hazel::KeyCode::KeyLeft
#define HZ_KEY_DOWN            ::Hazel::KeyCode::KeyDown
#define HZ_KEY_UP              ::Hazel::KeyCode::KeyUp
#define HZ_KEY_PAGE_UP         ::Hazel::KeyCode::KeyPageUp
#define HZ_KEY_PAGE_DOWN       ::Hazel::KeyCode::KeyPageDown
#define HZ_KEY_HOME            ::Hazel::KeyCode::KeyHome
#define HZ_KEY_END             ::Hazel::KeyCode::KeyEnd
#define HZ_KEY_CAPS_LOCK       ::Hazel::KeyCode::KeyCapsLock
#define HZ_KEY_SCROLL_LOCK     ::Hazel::KeyCode::KeyScrollLock
#define HZ_KEY_NUM_LOCK        ::Hazel::KeyCode::KeyNumLock
#define HZ_KEY_PRINT_SCREEN    ::Hazel::KeyCode::KeyPrintScreen
#define HZ_KEY_PAUSE           ::Hazel::KeyCode::KeyPause
#define HZ_KEY_F1              ::Hazel::KeyCode::KeyF1
#define HZ_KEY_F2              ::Hazel::KeyCode::KeyF2
#define HZ_KEY_F3              ::Hazel::KeyCode::KeyF3
#define HZ_KEY_F4              ::Hazel::KeyCode::KeyF4
#define HZ_KEY_F5              ::Hazel::KeyCode::KeyF5
#define HZ_KEY_F6              ::Hazel::KeyCode::KeyF6
#define HZ_KEY_F7              ::Hazel::KeyCode::KeyF7
#define HZ_KEY_F8              ::Hazel::KeyCode::KeyF8
#define HZ_KEY_F9              ::Hazel::KeyCode::KeyF9
#define HZ_KEY_F10             ::Hazel::KeyCode::KeyF10
#define HZ_KEY_F11             ::Hazel::KeyCode::KeyF11
#define HZ_KEY_F12             ::Hazel::KeyCode::KeyF12
#define HZ_KEY_F13             ::Hazel::KeyCode::KeyF13
#define HZ_KEY_F14             ::Hazel::KeyCode::KeyF14
#define HZ_KEY_F15             ::Hazel::KeyCode::KeyF15
#define HZ_KEY_F16             ::Hazel::KeyCode::KeyF16
#define HZ_KEY_F17             ::Hazel::KeyCode::KeyF17
#define HZ_KEY_F18             ::Hazel::KeyCode::KeyF18
#define HZ_KEY_F19             ::Hazel::KeyCode::KeyF19
#define HZ_KEY_F20             ::Hazel::KeyCode::KeyF20
#define HZ_KEY_F21             ::Hazel::KeyCode::KeyF21
#define HZ_KEY_F22             ::Hazel::KeyCode::KeyF22
#define HZ_KEY_F23             ::Hazel::KeyCode::KeyF23
#define HZ_KEY_F24             ::Hazel::KeyCode::KeyF24
#define HZ_KEY_F25             ::Hazel::KeyCode::KeyF25
#define HZ_KEY_KP_0            ::Hazel::KeyCode::KeyKP0
#define HZ_KEY_KP_1            ::Hazel::KeyCode::KeyKP1
#define HZ_KEY_KP_2            ::Hazel::KeyCode::KeyKP2
#define HZ_KEY_KP_3            ::Hazel::KeyCode::KeyKP3
#define HZ_KEY_KP_4            ::Hazel::KeyCode::KeyKP4
#define HZ_KEY_KP_5            ::Hazel::KeyCode::KeyKP5
#define HZ_KEY_KP_6            ::Hazel::KeyCode::KeyKP6
#define HZ_KEY_KP_7            ::Hazel::KeyCode::KeyKP7
#define HZ_KEY_KP_8            ::Hazel::KeyCode::KeyKP8
#define HZ_KEY_KP_9            ::Hazel::KeyCode::KeyKP9
#define HZ_KEY_KP_DECIMAL      ::Hazel::KeyCode::KeyKPDecimal
#define HZ_KEY_KP_DIVIDE       ::Hazel::KeyCode::KeyKPDivide
#define HZ_KEY_KP_MULTIPLY     ::Hazel::KeyCode::KeyKPMultiply
#define HZ_KEY_KP_SUBTRACT     ::Hazel::KeyCode::KeyKPSubtract
#define HZ_KEY_KP_ADD          ::Hazel::KeyCode::KeyKPAdd
#define HZ_KEY_KP_ENTER        ::Hazel::KeyCode::KeyKPEnter
#define HZ_KEY_KP_EQUAL        ::Hazel::KeyCode::KeyKPEqual
#define HZ_KEY_LEFT_SHIFT      ::Hazel::KeyCode::KeyLeftShift
#define HZ_KEY_LEFT_CONTROL    ::Hazel::KeyCode::KeyLeftControl
#define HZ_KEY_LEFT_ALT        ::Hazel::KeyCode::KeyLeftAlt
#define HZ_KEY_LEFT_SUPER      ::Hazel::KeyCode::KeyLeftSuper
#define HZ_KEY_RIGHT_SHIFT     ::Hazel::KeyCode::KeyRightShift
#define HZ_KEY_RIGHT_CONTROL   ::Hazel::KeyCode::KeyRightControl
#define HZ_KEY_RIGHT_ALT       ::Hazel::KeyCode::KeyRightAlt
#define HZ_KEY_RIGHT_SUPER     ::Hazel::KeyCode::KeyRightSuper
#define HZ_KEY_MENU            ::Hazel::KeyCode::KeyMenu
