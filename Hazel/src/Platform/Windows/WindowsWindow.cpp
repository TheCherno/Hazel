#include "hzpch.h"
#include "WindowsWindow.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/KeyEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

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
		m_Data.Mode = props.Mode;
		m_Data.WindowedWidth = props.Width;
		m_Data.WindowedHeight = props.Height;

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		GLFWmonitor* windowRenderScreen = glfwGetPrimaryMonitor(); // where the window will be rendered
		const GLFWvidmode* baseVideoMode = glfwGetVideoMode(windowRenderScreen);

		// Set the actual width and height
		switch (m_Data.Mode)
		{
			case WindowMode::Fullscreen:
				m_Data.Width = baseVideoMode->width;
				m_Data.Height = baseVideoMode->height;
				break;
			case WindowMode::Borderless:
				// TODO
			case WindowMode::Windowed:
				m_Data.Width = props.Width;
				m_Data.Height = props.Height;
				break;
		}

		HZ_CORE_INFO("Creating window '{0}' ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);

		// Create window in windowed mode
		glfwWindowHint(GLFW_DECORATED, m_Data.Mode == WindowMode::Windowed ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_RESIZABLE, m_Data.Mode == WindowMode::Windowed ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_FLOATING, m_Data.Mode == WindowMode::Fullscreen ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_AUTO_ICONIFY, m_Data.Mode == WindowMode::Fullscreen ? GLFW_TRUE : GLFW_FALSE);
		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(),
			m_Data.Mode == WindowMode::Windowed ? nullptr : windowRenderScreen, nullptr);

		if (m_Data.Mode == WindowMode::Windowed)
		{
			// Extract the position in windowed mode
			int Xpos, Ypos;
			glfwGetWindowPos(m_Window, &Xpos, &Ypos);
			m_Data.WindowedPos = { Xpos, Ypos };
		}

		// Now the window is constructed, we can create a context for it
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		// Set additional window parameters
		SetVSync(props.VSync);

		// Set GLFW callbacks
		glfwSetWindowUserPointer(m_Window, &m_Data);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowMaximizeCallback(m_Window, [](GLFWwindow* window, int maximised)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (maximised)
			{
				case GLFW_TRUE:
					data.Mode = WindowMode::Fullscreen;
					return;
				case GLFW_FALSE:
					data.Mode = WindowMode::Windowed;
					return;
			}
			HZ_CORE_ASSERT(false, "Invalid maximised value");
		});

		glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int posX, int posY)
		{
			if (posX == 0 && posY == 0)
				return; // Borderless, not moved

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.WindowedPos = { posX, posY };
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
		m_Context->SwapBuffers();
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
	
	void WindowsWindow::SetWindowMode(const WindowMode& mode)
	{
		if (mode == m_Data.Mode) return;
		m_Data.Mode = mode;

		GLFWmonitor* windowRenderScreen = glfwGetPrimaryMonitor(); // where the window will be rendered
		const GLFWvidmode* baseVideoMode = glfwGetVideoMode(windowRenderScreen);

		// Set the actual width and height
		switch (m_Data.Mode)
		{
			case WindowMode::Fullscreen:
				m_Data.Width = baseVideoMode->width;
				m_Data.Height = baseVideoMode->height;
				break;
			case WindowMode::Borderless:
				// TODO
			case WindowMode::Windowed:
				m_Data.Width = m_Data.WindowedWidth;
				m_Data.Height = m_Data.WindowedHeight;
				break;
		}

		HZ_CORE_ASSERT(m_Window, "Failed to retrieve window.");
		glfwSetWindowMonitor(m_Window,
		                     m_Data.Mode == WindowMode::Windowed ? nullptr : windowRenderScreen,
		                     m_Data.Mode == WindowMode::Windowed ? m_Data.WindowedPos.x : 0,
		                     m_Data.Mode == WindowMode::Windowed ? m_Data.WindowedPos.y : 0,
		                     m_Data.Width, m_Data.Height,
		                     baseVideoMode->refreshRate);

		glfwSetWindowAttrib(m_Window, GLFW_DECORATED, m_Data.Mode == WindowMode::Windowed ? GLFW_TRUE : GLFW_FALSE);
		glfwSetWindowAttrib(m_Window, GLFW_RESIZABLE, m_Data.Mode == WindowMode::Windowed ? GLFW_TRUE : GLFW_FALSE);
		glfwSetWindowAttrib(m_Window, GLFW_FLOATING, m_Data.Mode == WindowMode::Fullscreen ? GLFW_TRUE : GLFW_FALSE);
		glfwSetWindowAttrib(m_Window, GLFW_AUTO_ICONIFY, m_Data.Mode == WindowMode::Fullscreen ? GLFW_TRUE : GLFW_FALSE);

		if (glfwGetWindowAttrib(m_Window, GLFW_FLOATING) == GLFW_FALSE)
			glfwShowWindow(m_Window);
	}

}
