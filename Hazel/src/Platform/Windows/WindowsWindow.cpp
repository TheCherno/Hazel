#include "hzpch.h"
#include "WindowsWindow.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/KeyEvent.h"

#include <glad/glad.h>

namespace Hazel {
	
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		HZ_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_PrimaryMonitor = glfwGetPrimaryMonitor();

		m_BaseVideoMode = *(glfwGetVideoMode(m_PrimaryMonitor));
		HZ_CORE_TRACE("Storing underlying OS video mode: {0}x{1}@{2}Hz (r{3}g{4}b{5})",
			m_BaseVideoMode.width,
			m_BaseVideoMode.height,
			m_BaseVideoMode.refreshRate,
			m_BaseVideoMode.redBits,
			m_BaseVideoMode.greenBits,
			m_BaseVideoMode.blueBits);

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		// Change to windowed, fullscreen, or fullscreen borderless
		// Store current information about the window location and size (starting location/size)
		m_OldWindowedParams.Width = props.Width;
		m_OldWindowedParams.Height = props.Height;
		glfwGetWindowPos(m_Window, &(m_OldWindowedParams.XPos), &(m_OldWindowedParams.YPos));
		SetWindowMode(props.Mode, 0, 0);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize Glad!");
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::SetWindowMode(const WindowMode & mode, unsigned int width = 0, unsigned int height = 0)
	{
		if (!m_Window) // Ensure there is a window to work on
			return;
		if (mode == m_Data.Mode) // Nothing to do as this is not a change
			return;

		// If currently windowed, stash the current size and position of the window
		if (m_Data.Mode == WindowMode::WINDOWED) {
			m_OldWindowedParams.Width = m_Data.Width;
			m_OldWindowedParams.Height = m_Data.Height;
			glfwGetWindowPos(m_Window, &(m_OldWindowedParams.XPos), &(m_OldWindowedParams.YPos));

		}

		GLFWmonitor* monitor = nullptr;

		if (mode == WindowMode::BORDERLESS) {
			// For borderless full screen, the new width and height will be the video mode width and height
			width = m_BaseVideoMode.width;
			height = m_BaseVideoMode.height;
			monitor = m_PrimaryMonitor;
		}
		else if (mode == WindowMode::WINDOWED && (width == 0 || height == 0)) {
			// For windowed, use old window height and width if none provided
			width = m_OldWindowedParams.Width;
			height = m_OldWindowedParams.Height;
			// monitor = nullptr; 
		}
		else if (mode == WindowMode::FULL_SCREEN) {
			if (width == 0 || height == 0) {
				// Use the old window size
				// TODO: May want to change this to check if it is a valid full screen resolution pair
				width = m_Data.Width;
				height = m_Data.Height;
			}
			monitor = m_PrimaryMonitor;
		}

		// Update stored width and height
		m_Data.Width = width;
		m_Data.Height = height;

		// Trigger resize event
		if (m_Data.EventCallback) {
			WindowResizeEvent e(width, height);
			m_Data.EventCallback(e);
		}

		HZ_CORE_INFO("Changing window mode from {0} to {1}: [{2}, {3}]", m_Data.Mode, mode, width, height);

		// Record new window type
		m_Data.Mode = mode;

		glfwSetWindowMonitor(m_Window, monitor, m_OldWindowedParams.XPos, m_OldWindowedParams.YPos, width, height, m_BaseVideoMode.refreshRate);
	}
}
