project "Glad"
	kind "StaticLib"
	language "C"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}

	includedirs
	{
		"include"
	}

	filter "action:xcode4"
		sysincludedirs
		{
			"${PROJECT_DIR}/include"
		}
	
	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

	filter "system:macosx"
		systemversion "latest"
		staticruntime "On"
        
	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"

	filter { "system:macosx", "configurations:Release" }
		buildoptions "/MT"