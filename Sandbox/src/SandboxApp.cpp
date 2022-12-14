#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public Hazel::Application
{
public:
	Sandbox(const Hazel::ApplicationSpecification& specification)
		: Hazel::Application(specification)
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Hazel::Application* Hazel::CreateApplication(Hazel::ApplicationCommandLineArgs args)
{
	ApplicationSpecification spec;
	spec.Name = "Sandbox";
	spec.WorkingDirectory = "../Hazelnut";
	spec.CommandLineArgs = args;

	return new Sandbox(spec);
}
