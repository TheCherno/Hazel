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

	filter "system:windows"
		systemversion "latest"

	filter { "system:windows", "action:gmake*" }
		links
		{
			"GLFW",
			"Glad",
			"ImGui",
			"yaml-cpp",
			"OpenGL32",
			"gdi32",
			"comdlg32",
			"spirv-cross",
			"shaderc",
			"shaderc_util",
			"SPIRV-Tools-opt",
			"SPIRV-Tools",
			"MachineIndependent",
			"OSDependent",
			"GenericCodeGen",
			"OGLCompiler",
			"SPIRV"
		}

	filter "system:linux"
		links
		{
			"dl", 
			"pthread",
			"GLFW",
			"GL",
			"Glad",
			"ImGui",
			"yaml-cpp",
			"X11",
			"spirv-cross",
			"shaderc",
			"shaderc_util",
			"SPIRV-Tools-opt",
			"SPIRV-Tools",
			"MachineIndependent",
			"OSDependent",
			"GenericCodeGen",
			"OGLCompiler",
			"SPIRV"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"

	if os.getenv("VULKAN_SDK") ~= nil then
		filter { "configurations:Debug", "action:vs*" }
			postbuildcommands
			{
				"{COPYDIR} \"%{LibraryDir.VulkanSDK_DebugDLL}\" \"%{cfg.targetdir}\""
			}
	end

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"
