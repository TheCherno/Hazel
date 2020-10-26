#pragma once

#include "Hazel.h"
#include "Panels/SceneHierarchyPanel.h"

namespace Hazel {

	enum CustomEventTypes
	{
		TestEventType
	};

	class TestEvent : public CustomEvent
	{
	public:
		TestEvent() {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "TestEvent" << std::endl;
			return ss.str();
		}

		EVENT_CLASS_CUSTOM_TYPE(TestEventType)
	};

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;

		void OnCustomEvent(CustomEvent& e) override;
		bool OnTestEvent(TestEvent& e);
	private:
		bool OnKeyPressed(KeyPressedEvent& e);

		void NewScene();
		void OpenScene();
		void SaveSceneAs();
	private:
		Hazel::OrthographicCameraController m_CameraController;

		// Temp
		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;
		Ref<Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;

		bool m_PrimaryCamera = true;

		Ref<Texture2D> m_CheckerboardTexture;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
	};

}
