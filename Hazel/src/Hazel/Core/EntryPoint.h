#pragma once
#include "Hazel/Core/Base.h"
#include "Hazel/Core/Application.h"

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication(ApplicationCommandLineArgs args);

namespace Hazel
{
	int Main(int argc, char** argv)
	{
		Hazel::Log::Init();

		HZ_PROFILE_BEGIN_SESSION("Startup", "HazelProfile-Startup.json");
		auto app = Hazel::CreateApplication({ argc, argv });
		HZ_PROFILE_END_SESSION();

		HZ_PROFILE_BEGIN_SESSION("Runtime", "HazelProfile-Runtime.json");
		app->Run();
		HZ_PROFILE_END_SESSION();

		HZ_PROFILE_BEGIN_SESSION("Shutdown", "HazelProfile-Shutdown.json");
		delete app;
		HZ_PROFILE_END_SESSION();

		return 0;
	}
}

#ifdef HZ_DIST
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdLine, int cmdShow)
{
	return Hazel::Main(__argc, __argv);
}
#else
int main(int argc, char** argv)
{
	return Hazel::Main(argc, argv);
}
#endif // HZ_DIST

#endif
