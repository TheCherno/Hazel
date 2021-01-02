#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Hazel {
	#ifdef HZ_PLATFORM_WINDOWS
	extern "C" {
		__declspec(dllexport) uint32_t NvOptimusEnablement = 0x00000001;
		__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
	}
	#endif

	class Hazelnut : public Application
	{
	public:
		Hazelnut(ApplicationCommandLineArgs args)
			: Application("Hazelnut", args)
		{
			PushLayer(new EditorLayer());
		}

		~Hazelnut()
		{
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new Hazelnut(args);
	}

}
