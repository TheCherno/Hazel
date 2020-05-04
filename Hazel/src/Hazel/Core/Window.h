#pragma once

#include <string_view>
#include "hzpch.h"

#include "Hazel/Core/Core.h"
#include "Hazel/Events/Event.h"

namespace Hazel {


	// Interface representing a desktop system based Window
	class Window
	{
	public:
        struct Props
        {
            std::string Title;
            unsigned int Width;
            unsigned int Height;

            explicit Props(std::string_view title = "Hazel Engine",
                                 unsigned int width = 1280,
                                 unsigned int height = 720)
                    : Title(title), Width(width), Height(height)
            {
            }
        };

        using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		[[nodiscard]] virtual unsigned int GetWidth() const = 0;
		[[nodiscard]] virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		[[nodiscard]] virtual bool IsVSync() const = 0;

		[[nodiscard]] virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const Window::Props& props = Window::Props{});
	};

}