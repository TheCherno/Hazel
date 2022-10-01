project "Hazelnut"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Hazel/vendor/spdlog/include",
		"%{wks.location}/Hazel/src",
		"%{wks.location}/Hazel/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}"
	}

	links
	{
		"Hazel"
	}

	filter "system:linux"
		links
		{
			"GLFW",
			"Glad",
			"ImGui",
			"Xrandr",
			"Xi",
			"GLU",
			"GL",
			"X11",
			"dl",
			"pthread",
			"stdc++fs",	--GCC versions 5.3 through 8.x need stdc++fs for std::filesystem
			"yaml-cpp",
			"Box2D",

			"vulkan",
			"shaderc_shared",
			"spirv-cross-c",
			"spirv-cross-core",
			"spirv-cross-cpp",
			"spirv-cross-glsl",
			"spirv-cross-reflect",
			"spirv-cross-util",
			"spirv-cross-c-shared",
			"spirv-cross-hlsl",
			"spirv-cross-msl",
		}
		defines
		{
			"HZ_PLATFORM_LINUX"
		}

	filter "system:windows"
		systemversion "latest"
	
		defines
		{
			"HZ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"
