project "Hazel"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hzpch.h"
	pchsource "src/hzpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",

		"vendor/ImGuizmo/ImGuizmo.h",
		"vendor/ImGuizmo/ImGuizmo.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.VulkanSDK}",
		"%{IncludeDir.shaderc}",
		"%{IncludeDir.SPIRV_Cross}",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"yaml-cpp",
		"opengl32.lib"
	}

	filter "files:vendor/ImGuizmo/**.cpp"
	flags { "NoPCH" }

	filter { "system:windows", "action:vs*" }
		systemversion "latest"

		defines
		{
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"
	
	VULKAN_SDK = os.getenv("VULKAN_SDK")
	if VULKAN_SDK ~= nil then
		filter { "configurations:Debug", "action:vs*" }
			links
			{
				"%{Library.ShaderC_Debug}",
				"%{Library.SPIRV_Cross_Debug}",
				"%{Library.SPIRV_Cross_GLSL_Debug}"
			}
	end

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"

	if VULKAN_SDK ~= nil then
		filter { "configurations:Release", "action:vs*" }
			links
			{
				"%{Library.ShaderC_Release}",
				"%{Library.SPIRV_Cross_Release}",
				"%{Library.SPIRV_Cross_GLSL_Release}"
			}
	end

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"

	if VULKAN_SDK ~= nil then
		filter { "configurations:Dist", "action:vs*" }
			links
			{
				"%{Library.ShaderC_Release}",
				"%{Library.SPIRV_Cross_Release}",
				"%{Library.SPIRV_Cross_GLSL_Release}"
			}
	end

	if VULKAN_SDK == nil then
		filter { "action:vs*" }
			links
			{
				"%{Library.ShaderC}",
				"%{Library.ShaderC_Util}",

				"%{Library.SPIRV}",
				"%{Library.SPIRV_Cross}",
				"%{Library.SPIRV_Cross_MachineIndependent}",
				"%{Library.SPIRV_Cross_OSDependent}",
				"%{Library.SPIRV_Cross_GenericCodeGen}",
				"%{Library.SPIRV_Cross_OGLCompiler}",

				"%{Library.SPIRV_Tools_SPIRV_Tools}",
				"%{Library.SPIRV_Tools_Opt}",
			}
	end
