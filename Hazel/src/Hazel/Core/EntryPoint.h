#pragma once
#include "Hazel/Core/Base.h"

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	Hazel::Log::Init();

#ifdef HZ_PLATFORM_LINUX
	HZ_CORE_WARN("Linux is not fully supported!");
	HZ_CORE_WARN("Hazel for Linux currently uses Hazel::WindowsInput!"); // See Input::Create()
#endif

	HZ_PROFILE_BEGIN_SESSION("Startup", "HazelProfile-Startup.json");
	auto app = Hazel::CreateApplication();
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("Runtime", "HazelProfile-Runtime.json");
	app->Run();
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("Startup", "HazelProfile-Shutdown.json");
	delete app;
	HZ_PROFILE_END_SESSION();
}
