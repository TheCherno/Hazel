#pragma once
#include "Hazel/Core/Core.h"

#ifdef HZ_PROFILE
#include <filesystem>
#endif

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	Hazel::Log::Init();

	std::filesystem::path binDirectory = std::filesystem::path(argv[0]).remove_filename();

	HZ_PROFILE_BEGIN_SESSION("Startup", (binDirectory / "HazelProfile-Startup.json").string());
	auto app = Hazel::CreateApplication();
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("Runtime", (binDirectory / "HazelProfile-Runtime.json").string());
	app->Run();
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("Startup", (binDirectory / "HazelProfile-Shutdown.json").string());
	delete app;
	HZ_PROFILE_END_SESSION();
}

#endif
