#include "hzpch.h"
#include "Platform/Linux-Xlib/XlibWindow.h"

#include "Hazel/Core/Input.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/KeyEvent.h"

#include "Hazel/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Hazel {
	
	static s_WindowCount = 0;

	XlibWindow::XlibWindow(const WindowProps& props)
	{
		HZ_PROFILE_FUNCTION();

		Init(props);
	}

	XlibWindow::~XlibWindow()
	{
		HZ_PROFILE_FUNCTION();

		Shutdown();
	}

	void CreateContext(GLXFBConfig& fbconfig)
	{
		typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

		glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
		glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddressARB((const unsigned char*)"glXCreateContextAttribsARB");

		GLXContext context = 0;
		/* OpenGL 3.3 */
		int attribs[] =
		{
			0x2091, 3,
			0x2092, 3,
			None
		};
		context = glXCreateContextAttribsARB(dis, fbconfig, 0, True, attribs);
		
		/* That should be in OpenGLContext::Init() */
		glXMakeCurrent(m_Display, m_Window, context);
	}

	int CreateWindow(int width, int height, const char *title)
	{
		/* Check GLX version */
		
		GLXFBConfig *fbc;
		int attribs[] =
		{
			GLX_X_RENDERABLE,	True,
			GLX_DRAWABLE_TYPE,	GLX_WINDOW_BIT,
			GLX_RENDER_TYPE,		GLX_RGBA_BIT,
			GLX_X_VISUAL_TYPE,	GLX_TRUE_COLOR,
			GLX_RED_SIZE,			8,
			GLX_GREEN_SIZE,		8,
			GLX_BLUE_SIZE,		8,
			GLX_ALPHA_SIZE,		8,
			GLX_DEPTH_SIZE,		24,
			GLX_STENCIL_SIZE,		8,
			GLX_DOUBLEBUFFER,	True,
			None
		};

		int fb_count;
		fbc = glXChooseFBConfig(m_Display, DefaultScreen(m_Display), attribs, &fb_count);
		/* check if fbc = 0 */

		int best_fbc = -1, worst_fbc = -1, best_samp = -1, worst_samp = 999;
		for (int i = 0; i < fb_count; ++i)
		{
			XVisualInfo *tvi = glXGetVisualFromFBConfig(dp->dis, fbc[i]);
			if (tvi)
			{
				int samp_buf, samples;
				glXGetFBConfigAttrib(m_Display, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf);
				glXGetFBConfigAttrib(m_Display, fbc[i], GLX_SAMPLES, &samples);
				if (best_fbc < 0 || (samp_buf && samples > best_samp))
				{
					best_fbc = i;
					best_samp = samples;
				}
				if (worst_fbc < 0 || !samp_buf || samples < worst_samp)
				{
					worst_fbc = i;
					worst_samp = samples;
				}
			}
		}
		GLXFBConfig best = fbc[best_fbc];
		XFree(fbc);
		XVisualInfo *vi = glXGetVisualFromFBConfig(m_Display, best);

		XSetWindowAttributes swa;
		swa.colomap = XCreateColormap(dp->dis, root, vis, AllocNone);
		swa.background_pixmap = None;
		swa.event_mask = ; /* Events */

		int root = XRootWindow(dp->dis, vi->screen);

		XCreateWindow(m_Display, root, 0, 0, width, height, 0, vi->depth, InputOutput, vi->visual, mask, &swa);
		XStroreName(m_Display, m_Window, title);
		XMapWindow(m_Display, m_Window);

		XFree(vi);

		CreateContext(best);
	}

	void XlibWindow::Init(const WindowProps& props)
	{
		HZ_PROFILE_FUNCTION();

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (s_WindowCount == 0)
		{
			Display *dis = XOpenDisplay(0);
			if (dis == nullptr)
			{
				HZ_CORE_ERROR("Xlib Error: Failed to connect to the X server.");
			}	
		}

		{
		#if defined(HZ_DEBUG)
			if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
				bool debug = true;
		#endif
			m_Window = CreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str());
			++s_WindowCount;
		}
		
		/* CreateWindow() also calls CreateContext() */
		/* It's outside the OpenGLContext class because it uses GLFW */

		SetVSync(true);
	}

	void WindowsWindow::Shutdown()
	{
		HZ_PROFILE_FUNCTION();

		XDestroyWindow(m_Display, m_Window);
		--s_WindowCount;

		if (s_WindowCount == 0)
		{
			XCloseDisplay(m_Display);
		}
	}

	void WindowsWindow::OnUpdate()
	{
		HZ_PROFILE_FUNCTION();

		if (XPending(m_Display))
		{
			XNextEvent(m_Display, &m_Event);
			switch (m_Event.type)
			{
 				/* Handle Events */
			}
		}
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		HZ_PROFILE_FUNCTION();

		if (enabled)
			glXSwapInterval();
		else
			glXSwapInterval();

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}
