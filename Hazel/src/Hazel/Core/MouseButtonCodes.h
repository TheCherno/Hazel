#pragma once

namespace Hazel
{
    enum class MouseButtons
    {
        // From glfw3.h
        Button1                 = 0,
        Button2                 = 1,
        Button3                 = 2,
        Button4                 = 3,
        Button5                 = 4,
        Button6                 = 5,
        Button7                 = 6,
        Button8                 = 7,

        ButtonLeft              = Button1,
        ButtonRight             = Button2,
        ButtonMiddle            = Button3,

        ButtonLast              = Button8,
    };
}

/* Macro defines are kept for ensuring backward-compatibility.
 * All taken from glfw3.h.
 */

 // From glfw3.h
#define HZ_MOUSE_BUTTON_1         0
#define HZ_MOUSE_BUTTON_2         1
#define HZ_MOUSE_BUTTON_3         2
#define HZ_MOUSE_BUTTON_4         3
#define HZ_MOUSE_BUTTON_5         4
#define HZ_MOUSE_BUTTON_6         5
#define HZ_MOUSE_BUTTON_7         6
#define HZ_MOUSE_BUTTON_8         7
#define HZ_MOUSE_BUTTON_LAST      HZ_MOUSE_BUTTON_8
#define HZ_MOUSE_BUTTON_LEFT      HZ_MOUSE_BUTTON_1
#define HZ_MOUSE_BUTTON_RIGHT     HZ_MOUSE_BUTTON_2
#define HZ_MOUSE_BUTTON_MIDDLE    HZ_MOUSE_BUTTON_3
