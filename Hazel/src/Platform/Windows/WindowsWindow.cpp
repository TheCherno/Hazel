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
		m_Data.WindowedWidth = props.Width;
		m_Data.WindowedHeight = props.Height;

		HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}
		
		// Create window in windowed mode
		m_Data.Mode = WindowMode::Windowed;
		glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);

		int Xpos, Ypos;
		glfwGetWindowPos(m_Window, &Xpos, &Ypos);
		m_Data.WindowedPos = { Xpos, Ypos };

		SetVSync(props.VSync);

		// Change mode if needed
		if (m_Data.Mode != props.Mode)
			SetWindowMode(props.Mode);
		
		// Set GLFW callbacks
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
					data.Mode = WindowMode::FullScreen;
					return;
				case GLFW_FALSE:
					data.Mode = WindowMode::Windowed;
					return;
			}
			HZ_CORE_ERROR("Invalid maximised value");
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
		HZ_CORE_ASSERT(m_Window, "Failed to retrieve window.");
		if (mode == m_Data.Mode) return;

		GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
		GLFWvidmode baseVideoMode = *(glfwGetVideoMode(primaryMonitor));

		int windowPosX = 0, windowPosY = 0;
		GLFWmonitor* monitor = nullptr;
		int windowDecorated = GLFW_TRUE;
		int windowResizeable = GLFW_TRUE;
		int windowAutoIconify = GLFW_FALSE;

		switch (mode)
		{
			default:
				HZ_CORE_ERROR("WindowMode not supported.");
			case WindowMode::Windowed:
			{
				m_Data.Width = m_Data.WindowedWidth;
				m_Data.Height = m_Data.WindowedHeight;
				windowPosX = m_Data.WindowedPos.x;
				windowPosY = m_Data.WindowedPos.y;
				break;
			}
			case WindowMode::Borderless:
			{
				m_Data.Width = baseVideoMode.width;
				m_Data.Height = baseVideoMode.height;
				monitor = primaryMonitor;
				windowDecorated = GLFW_FALSE;
				windowResizeable = GLFW_FALSE;
				windowAutoIconify = GLFW_TRUE;
				break;
			}
			case WindowMode::FullScreen:
			{
				// Achieved by creating a windowed window with size of monitor
				int border = 0, headerBorder = 100;
				glm::uvec4 taskbar = { 0, 0, 0 , 100}; // x = left; y = top; z = right; w = bottom
				/* TODO:
					- Make a struct screenproperties (static part of Window?) -> specify for each screen:
						- Extract frame borders of the window (headerBorder, border)
						- Extract location from taskbar as well (could be 0 if it is hidden)
					- Accomodate this in WindowPosCallback (compensate for fullscreen)
				*/
				windowPosX = border + taskbar.x;
				windowPosY = headerBorder + taskbar.y;
				m_Data.Width = baseVideoMode.width - 2 * border - taskbar.x - taskbar.z;
				m_Data.Height = baseVideoMode.height - headerBorder - border - taskbar.y - taskbar.w;
				break;
			}
		}

		glfwSetWindowMonitor(m_Window, monitor,
		                     windowPosX, windowPosY,
		                     m_Data.Width, m_Data.Height,
		                     baseVideoMode.refreshRate);
		glfwSetWindowAttrib(m_Window, GLFW_DECORATED, windowDecorated);
		glfwSetWindowAttrib(m_Window, GLFW_RESIZABLE, windowResizeable);
		glfwSetWindowAttrib(m_Window, GLFW_AUTO_ICONIFY, windowAutoIconify);
		m_Data.Mode = mode;
	}

}
