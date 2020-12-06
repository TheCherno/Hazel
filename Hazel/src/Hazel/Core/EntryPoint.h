#pragma once
#include "Hazel/Core/Base.h"
#include "Hazel/Core/Application.h"

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication(ApplicationCommandLineArgs args);

<<<<<<< HEAD
extern "C" {
	__declspec(dllexport) uint32_t NvOptimusEnablement = 0x00000001;
}

extern "C" {
	__declspec(dllexport) uint32_t NvOptimusEnablement = 0x00000001;
}

extern "C" {
	__declspec(dllexport) uint32_t NvOptimusEnablement = 0x00000001;
}

int main(int argc, char** argv)
{
>>>>>>> 9ee977d... Updated as per @lovely_santa 's suggestion
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
}

#endif
