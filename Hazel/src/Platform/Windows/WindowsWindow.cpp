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
		m_Data.WindowedMaximised = false;
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
			case WindowMode::Borderless:
			case WindowMode::Fullscreen:
				m_Data.Width = baseVideoMode->width;
				m_Data.Height = baseVideoMode->height;
				break;
			case WindowMode::Windowed:
				m_Data.Width = props.Width;
				m_Data.Height = props.Height;
				break;
		}

		HZ_CORE_INFO("Creating window '{0}' ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);

		glfwWindowHint(GLFW_DECORATED, m_Data.Mode == WindowMode::Windowed ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_RESIZABLE, m_Data.Mode == WindowMode::Windowed ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_FLOATING, m_Data.Mode == WindowMode::Fullscreen ? GLFW_TRUE : GLFW_FALSE);
		glfwWindowHint(GLFW_AUTO_ICONIFY, m_Data.Mode == WindowMode::Fullscreen ? GLFW_TRUE : GLFW_FALSE);
		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(),
			m_Data.Mode == WindowMode::Windowed ? nullptr : windowRenderScreen, nullptr);

		if (m_Data.Mode == WindowMode::Windowed)
		{
			// Extract the position in windowed mode
			glfwGetWindowPos(m_Window, &m_Data.WindowedPos.x, &m_Data.WindowedPos.y);
		}
		else if (m_Data.Mode == WindowMode::Borderless)
			glfwMaximizeWindow(m_Window);

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
			if (data.Mode == WindowMode::Windowed && !data.WindowedMaximised)
			{
				data.WindowedWidth = width;
				data.WindowedHeight = height;
			}

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowMaximizeCallback(m_Window, [](GLFWwindow* window, int maximized)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			if (data.Mode == WindowMode::Windowed)
				data.WindowedMaximised = maximized == GLFW_TRUE ? true : false;
		});

		glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int posX, int posY)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			if (data.Mode == WindowMode::Windowed)
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
		HZ_CORE_TRACE("Swapping to mode '{0}'", mode == WindowMode::Windowed ? "Windowed" : mode == WindowMode::Fullscreen ? "Fullscreen" : "Borderless");

		GLFWmonitor* windowRenderScreen = glfwGetPrimaryMonitor(); // where the window will be rendered
		const GLFWvidmode* baseVideoMode = glfwGetVideoMode(windowRenderScreen);

		// Disable callbacks temporarily, to prevent multiple resize events firing during this scope
		auto resizeCallbackFn = glfwSetWindowSizeCallback(m_Window, NULL);
		auto moveCallbackFn = glfwSetWindowPosCallback(m_Window, NULL);
		auto maximizeCallbackFn = glfwSetWindowMaximizeCallback(m_Window, NULL);

		glm::i32vec2 oldPos, newPos;
		glfwGetWindowPos(m_Window, &oldPos.x, &oldPos.y);

		switch (m_Data.Mode)
		{
			case WindowMode::Borderless:
				glfwRestoreWindow(m_Window);
				break;
			case WindowMode::Fullscreen:
				break;
			case WindowMode::Windowed:
				if (m_Data.WindowedMaximised)
				{
					glfwRestoreWindow(m_Window);
					glfwGetWindowPos(m_Window, &newPos.x, &newPos.y);
					m_Data.WindowedPos = newPos;
				}
				break;
		}

		int width, height;
		switch (mode)
		{
			case WindowMode::Borderless:
				width = baseVideoMode->width;
				height = baseVideoMode->height;
				break;
			case WindowMode::Fullscreen:
				width = baseVideoMode->width;
				height = baseVideoMode->height;
				break;
			case WindowMode::Windowed:
				width = m_Data.WindowedWidth;
				height = m_Data.WindowedHeight;
				break;
		}

		HZ_CORE_ASSERT(m_Window, "Failed to retrieve window.");
		m_Data.Mode = mode;
		glfwSetWindowAttrib(m_Window, GLFW_DECORATED, m_Data.Mode == WindowMode::Windowed ? GLFW_TRUE : GLFW_FALSE);
		glfwSetWindowAttrib(m_Window, GLFW_RESIZABLE, m_Data.Mode == WindowMode::Windowed ? GLFW_TRUE : GLFW_FALSE);
		glfwSetWindowAttrib(m_Window, GLFW_FLOATING, m_Data.Mode == WindowMode::Fullscreen ? GLFW_TRUE : GLFW_FALSE);
		glfwSetWindowAttrib(m_Window, GLFW_AUTO_ICONIFY, m_Data.Mode == WindowMode::Fullscreen ? GLFW_TRUE : GLFW_FALSE);
		glfwSetWindowMonitor(m_Window,
		                     m_Data.Mode == WindowMode::Fullscreen ? windowRenderScreen : nullptr,
		                     m_Data.Mode == WindowMode::Windowed ? m_Data.WindowedPos.x : 0,
		                     m_Data.Mode == WindowMode::Windowed ? m_Data.WindowedPos.y : 0,
		                     width, height,
		                     baseVideoMode->refreshRate);
		if (m_Data.Mode == WindowMode::Borderless || (m_Data.Mode == WindowMode::Windowed && m_Data.WindowedMaximised))
			glfwMaximizeWindow(m_Window);

		// re-enable callbacks
		glfwSetWindowSizeCallback(m_Window, resizeCallbackFn);
		glfwSetWindowPosCallback(m_Window, moveCallbackFn);
		glfwSetWindowMaximizeCallback(m_Window, maximizeCallbackFn);

		// manually raising a single resize event if needed (in correct order)
		glfwGetWindowPos(m_Window, &newPos.x, &newPos.y);
		if (oldPos != newPos)
			moveCallbackFn(m_Window, newPos.x, newPos.y);
		glfwGetWindowSize(m_Window, &width, &height);
		if (width != m_Data.Width || height != m_Data.Height)
			resizeCallbackFn(m_Window, width, height);

		if (glfwGetWindowAttrib(m_Window, GLFW_FLOATING) == GLFW_FALSE)
			glfwShowWindow(m_Window);
	}

}
