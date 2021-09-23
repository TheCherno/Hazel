project "spirv-cross"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"spirv_cross/**.h",
		"spirv_cross/**.cpp"
	}

	includedirs
	{
		"spirv_cross/"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "off"

	filter "action:gmake*"
		buildoptions { "-fdiagnostics-color=always -Wall -Wextra -Wshadow -Wno-deprecated-declarations" }


	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
