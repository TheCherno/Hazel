#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "ExampleLayer.h"

class ExampleApp : public Hazel::Application
{
public:
	ExampleApp()
	{
		PushLayer(new ExampleLayer());
	}

	~ExampleApp()
	{
	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new ExampleApp();
}
