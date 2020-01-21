#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "ExampleLayer.h"

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}
