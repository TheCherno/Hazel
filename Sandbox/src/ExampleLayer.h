#pragma once

#include "Hazel.h"

enum CustomEventTypes
{
	TestEventType
};

class TestEvent : public Hazel::CustomEvent
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

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Hazel::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Hazel::Event& e) override;

	bool OnTestEvent(TestEvent& e);
	void OnCustomEvent(Hazel::CustomEvent& e);
private:
	Hazel::ShaderLibrary m_ShaderLibrary;
	Hazel::Ref<Hazel::Shader> m_Shader;
	Hazel::Ref<Hazel::VertexArray> m_VertexArray;

	Hazel::Ref<Hazel::Shader> m_FlatColorShader;
	Hazel::Ref<Hazel::VertexArray> m_SquareVA;

	Hazel::Ref<Hazel::Texture2D> m_Texture, m_ChernoLogoTexture;

	Hazel::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

