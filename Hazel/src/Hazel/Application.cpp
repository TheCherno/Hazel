#include "hzpch.h"
#include "Application.h"

#include "Hazel/Log.h"

#include "Hazel/Renderer/Renderer.h"

#include "Input.h"

#include <GLFW/glfw3.h>
#include <filesystem>

namespace Hazel {

	Application* Application::s_Instance = nullptr;

	Application::Application(std::string base_directory)
	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_BaseDirectory = base_directory;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(HZ_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	std::string Application::CorrectFilePath(const std::string& path)
	{
		#if defined(HZ_DEBUG) || defined(HZ_RELEASE)
			if (std::filesystem::exists(path))	//Unmodified path check
				return path;

			auto check_path = std::filesystem::path(".") / m_BaseDirectory / path;	//Subdirectory of project
			if (std::filesystem::exists(check_path))
				return check_path;

			check_path = std::filesystem::path("../../..") / m_BaseDirectory / path;	//Decend to project directory from executable's directory
			if (std::filesystem::exists(check_path))
				return check_path;
		#endif

		return path;
	}
}
