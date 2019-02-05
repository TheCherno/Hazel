workspace "Hazel"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Hazel/vendor/GLFW/include"
IncludeDir["Glad"] = "Hazel/vendor/Glad/include"
IncludeDir["ImGui"] = "Hazel/vendor/imgui"

include "Hazel/vendor/GLFW"
include "Hazel/vendor/Glad"
include "Hazel/vendor/imgui"

project "Hazel"
    location "Hazel"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "hzpch.h"
    pchsource "Hazel/src/hzpch.cpp"

    -- Add all source and header files
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    -- Exclude all folders in Platform, since no all platforms need all of these
    removefiles { "%{prj.name}/src/Platform/**" }

    -- Except OpenGL ones, those are needed on all platforms
    files
    {
        "%{prj.name}/src/Platform/OpenGL/**.h",
        "%{prj.name}/src/Platform/OpenGL/**.cpp",
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
    }

    filter "system:linux"
        pic "On"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        -- Add Linux-specific files
        files
        {
            "%{prj.name}/src/Platform/Linux/**.h",
            "%{prj.name}/src/Platform/Linux/**.cpp"
        }

        files
        {
            "%{prj.name}/src/Platform/Windows/**.h",
            "%{prj.name}/src/Platform/Windows/**.cpp",
        }

        links
        {
            "Xrandr",
            "Xi",
            "GLEW",
            "GLU",
            "GL",
            "X11"
        }

        defines
        {
            "HZ_PLATFORM_LINUX",
            "HZ_BUILD_DLL"
        }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        -- Add Windows-specific files
        files
        {
            "%{prj.name}/src/Platform/Windows/**.h",
            "%{prj.name}/src/Platform/Windows/**.cpp"
        }


        links
        {
            "opengl32.lib"
        }

        defines
        {
            "HZ_PLATFORM_WINDOWS",
            "HZ_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
        }

    filter "configurations:Debug"
        defines "HZ_DEBUG"
        runtime "Debug"
        symbols "On"
    filter { "system:windows", "configurations:Debug" }
        buildoptions "/MDd"

    filter "configurations:Release"
        defines "HZ_RELEASE"
        runtime "Release"
        optimize "On"
    filter { "system:windows", "configurations:Release" }
        buildoptions "/MD"

    filter "configurations:Dist"
        defines "HZ_DIST"
        runtime "Release"
        optimize "On"
    filter { "system:windows", "configurations:Dist" }
        buildoptions "/MD"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Hazel/vendor/spdlog/include",
        "Hazel/src"
    }

    links
    {
        "Hazel"
    }

    filter "system:linux"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
        pic "On"

        defines
        {
            "HZ_PLATFORM_LINUX"
        }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "HZ_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "HZ_DEBUG"
        runtime "Debug"
        symbols "On"
    filter { "system:windows", "configurations:Debug" }
        buildoptions "/MDd"

    filter "configurations:Release"
        defines "HZ_RELEASE"
        runtime "Release"
        optimize "On"
    filter { "system:windows", "configurations:Release" }
        buildoptions "/MD"

    filter "configurations:Dist"
        defines "HZ_DIST"
        runtime "Release"
        optimize "On"

