#pragma once

#include "hzpch.h"

#include "Hazel/Core.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Renderer/GraphicsContext.h"

namespace Hazel {
	
	enum class WindowMode : uint8_t
	{
		// Definitions see https://stackoverflow.com/questions/34462445/fullscreen-vs-borderless-window/50452322#50452322
		Windowed,   // A windowed window with decorations
		Borderless, // A windowed window without decorations utilizing full display space
		Fullscreen  // A window using the full screen
	};

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		bool VSync;
		WindowMode Mode;

		WindowProps(const std::string& title = "Hazel Engine",
		            unsigned int width = 1280,
		            unsigned int height = 720,
		            WindowMode mode = WindowMode::Windowed,
		            bool VSync = true)
			: Title(title), Width(width), Height(height), VSync(VSync), Mode(mode)
		{
		}
	};

	// Interface representing a desktop system based Window
	class HAZEL_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		virtual void SetWindowMode(const WindowMode& mode) = 0;

		virtual void* GetNativeWindow() const = 0;
		virtual GraphicsContext* GetContext() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};

}
