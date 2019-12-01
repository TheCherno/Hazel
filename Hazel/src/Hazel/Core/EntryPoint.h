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

	HZ_PROFILE_BEGIN_SESSION("Startup", (std::filesystem::temp_directory_path() / "HazelProfile-Startup.json").string());
	auto app = Hazel::CreateApplication();
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("Runtime", (std::filesystem::temp_directory_path() / "HazelProfile-Runtime.json").string());
	app->Run();
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("Startup", (std::filesystem::temp_directory_path() / "HazelProfile-Shutdown.json").string());
	delete app;
	HZ_PROFILE_END_SESSION();
}

#endif
