cmake_minimum_required(VERSION 3.20)

# Set the project name
project(Hazel VERSION 1.0 LANGUAGES CXX C)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

########################################################################
# For GTK
option(HZ_BUILD_LINUX "Build Hazel to run on Linux platforms using GTK specific APIs" OFF)
if (HZ_BUILD_LINUX)
  # The `pkg_check_modules` function is created with this call
  find_package(PkgConfig REQUIRED)

  # These calls create special `PkgConfig::<MODULE>` variables
  pkg_check_modules(GTKMM_PKG IMPORTED_TARGET gtkmm-3.0)
endif()

########################################################################
# To use GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${Hazel_SOURCE_DIR}/Hazel/vendor/GLFW)
set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)
add_subdirectory(${Hazel_SOURCE_DIR}/Hazel/vendor/glm)
find_package(OpenGL REQUIRED)

add_subdirectory(${Hazel_SOURCE_DIR}/Hazel/vendor/yaml-cpp)
set(YAML_CPP_BUILD_TESTS=OFF CACHE BOOL "" FORCE)

########################################################################
# CXX FLAGS
#set(CMAKE_CXX_FLAGS "-Wall -Wextra -DGLFW_INCLUDE_NONE")
set(CMAKE_CXX_FLAGS "-DGLFW_INCLUDE_NONE")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DHZ_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

########################################################################
# For Vulkan support
find_package(Vulkan REQUIRED COMPONENTS glslang shaderc_combined SPIRV-Tools)

if(NOT Vulkan_FOUND)
  message(FATAL_ERROR "Vulkan::Vulkan was NOT found!")
endif()

add_library(shaderc_combined_lib INTERFACE)
if(Vulkan_shaderc_combined_FOUND)
  target_link_libraries(shaderc_combined_lib Vulkan::shaderc_combined)
else()
  message("Vulkan::shaderc_combined was NOT found!")
  message(" Attempting to set manually...")
  add_library(shaderc_combined_tmp STATIC IMPORTED)
  set_target_properties(shaderc_combined_tmp PROPERTIES
    IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libshaderc_combined.a"
    INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
  )
  target_link_libraries(shaderc_combined_lib INTERFACE
    shaderc_combined_tmp
  )
endif()

########################################################################
# For spirv-cross
add_library(spirv-cross INTERFACE)

add_library(spirv-cross-c_lib STATIC IMPORTED)
set_target_properties(spirv-cross-c_lib PROPERTIES
  IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libspirv-cross-c.a"
  INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
)
add_library(spirv-cross-core_lib STATIC IMPORTED)
set_target_properties(spirv-cross-core_lib PROPERTIES
  IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libspirv-cross-core.a"
  INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
)
add_library(spirv-cross-cpp_lib STATIC IMPORTED)
set_target_properties(spirv-cross-cpp_lib PROPERTIES
  IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libspirv-cross-cpp.a"
  INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
)
add_library(spirv-cross-glsl_lib STATIC IMPORTED)
set_target_properties(spirv-cross-glsl_lib PROPERTIES
  IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libspirv-cross-glsl.a"
  INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
)
add_library(spirv-cross-hlsl_lib STATIC IMPORTED)
set_target_properties(spirv-cross-hlsl_lib PROPERTIES
  IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libspirv-cross-hlsl.a"
  INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
)
add_library(spirv-cross-msl_lib STATIC IMPORTED)
set_target_properties(spirv-cross-msl_lib PROPERTIES
  IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libspirv-cross-msl.a"
  INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
)
add_library(spirv-cross-reflect_lib STATIC IMPORTED)
set_target_properties(spirv-cross-reflect_lib PROPERTIES
  IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libspirv-cross-reflect.a"
  INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
)
add_library(spirv-cross-util_lib STATIC IMPORTED)
set_target_properties(spirv-cross-util_lib PROPERTIES
  IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libspirv-cross-util.a"
  INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
)

target_link_libraries(spirv-cross INTERFACE
  spirv-cross-c_lib
  spirv-cross-core_lib
  spirv-cross-cpp_lib
  spirv-cross-glsl_lib
  spirv-cross-hlsl_lib
  spirv-cross-msl_lib
  spirv-cross-reflect_lib
  spirv-cross-util_lib
)

########################################################################
# For Box2D support
set(BOX2D_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "" FORCE)
add_subdirectory(${Hazel_SOURCE_DIR}/Hazel/vendor/Box2D)

########################################################################
# For Mono support
option(HZ_BUILD_LINUX "Build Hazel to run on Linux platforms using Mono specific APIs" OFF)
if (HZ_BUILD_LINUX)
  # These calls create special `PkgConfig::<MODULE>` variables
  pkg_check_modules(MONO_PKG IMPORTED_TARGET mono-2 monosgen-2)
endif()

########################################################################
# Include directories
include_directories(
  ${Hazel_SOURCE_DIR}/Hazel/src
  ${Hazel_SOURCE_DIR}/Hazel/vendor
  ${Hazel_SOURCE_DIR}/Hazel/vendor/spdlog/include
  ${Hazel_SOURCE_DIR}/Hazel/vendor/GLFW/include
  ${Hazel_SOURCE_DIR}/Hazel/vendor/Glad/include
  ${Hazel_SOURCE_DIR}/Hazel/vendor/imgui
  ${Hazel_SOURCE_DIR}/Hazel/vendor/glm
  ${Hazel_SOURCE_DIR}/Hazel/vendor/stb_image
  ${Hazel_SOURCE_DIR}/Hazel/vendor/entt/include
  ${Hazel_SOURCE_DIR}/Hazel/vendor/yaml-cpp/include
  ${Hazel_SOURCE_DIR}/Hazel/vendor/ImGuizmo
  ${Hazel_SOURCE_DIR}/Hazel/vendor/Box2D/include
  ${Hazel_SOURCE_DIR}/Hazel/vendor/filewatch
)

########################################################################
# Compile C# scripts
add_subdirectory(${Hazel_SOURCE_DIR}/Hazel-ScriptCore)
add_subdirectory(${Hazel_SOURCE_DIR}/Hazelnut/SandboxProject/Assets/Scripts)

########################################################################
# Add libraries
add_library(ImGuizmo
  ${Hazel_SOURCE_DIR}/Hazel/vendor/ImGuizmo/ImGuizmo.cpp
)

add_library(stb_image
  ${Hazel_SOURCE_DIR}/Hazel/vendor/stb_image/stb_image.cpp
)

add_library(glad
  ${Hazel_SOURCE_DIR}/Hazel/vendor/Glad/src/glad.c
)

add_library(imgui
  ${Hazel_SOURCE_DIR}/Hazel/vendor/imgui/imgui.cpp
  ${Hazel_SOURCE_DIR}/Hazel/vendor/imgui/imgui_draw.cpp
  ${Hazel_SOURCE_DIR}/Hazel/vendor/imgui/imgui_widgets.cpp
  ${Hazel_SOURCE_DIR}/Hazel/vendor/imgui/imgui_demo.cpp
)

add_library(HZ_Hazel_Project
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Project/ProjectSerializer.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Project/Project.cpp
)

add_library(HZ_Hazel_Scripting
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Scripting/ScriptGlue.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Scripting/ScriptEngine.cpp
)

add_library(HZ_Hazel_Math
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Math/Math.cpp
)

add_library(HZ_Hazel_Scene
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Scene/Scene.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Scene/Entity.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Scene/SceneCamera.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Scene/SceneSerializer.cpp
)

add_library(HZ_Hazel_ImGui
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/ImGui/ImGuiLayer.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/ImGui/ImGuiBuild.cpp
)

add_library(HZ_Hazel_Renderer
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Renderer/Shader.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Renderer/Buffer.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Renderer/GraphicsContext.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Renderer/Renderer.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Renderer/Renderer2D.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Renderer/VertexArray.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Renderer/RenderCommand.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Renderer/RendererAPI.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Renderer/OrthographicCamera.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Renderer/Texture.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Renderer/OrthographicCameraController.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Renderer/Framebuffer.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Renderer/EditorCamera.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Renderer/UniformBuffer.cpp
)

add_library(HZ_Platform_OpenGL
  ${Hazel_SOURCE_DIR}/Hazel/src/Platform/OpenGL/OpenGLContext.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Platform/OpenGL/OpenGLBuffer.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Platform/OpenGL/OpenGLVertexArray.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Platform/OpenGL/OpenGLRendererAPI.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Platform/OpenGL/OpenGLShader.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Platform/OpenGL/OpenGLTexture.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Platform/OpenGL/OpenGLFramebuffer.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Platform/OpenGL/OpenGLUniformBuffer.cpp
)

add_library(HZ_Platform_Linux
  ${Hazel_SOURCE_DIR}/Hazel/src/Platform/Linux/LinuxWindow.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Platform/Linux/LinuxInput.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Platform/Linux/LinuxPlatformUtils.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Platform/Linux/LinuxDialogWindow.cpp
)

add_library(HZ_Hazel_Core
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Core/Application.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Core/Log.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Core/Layer.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Core/LayerStack.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Core/Window.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Core/UUID.cpp
  ${Hazel_SOURCE_DIR}/Hazel/src/Hazel/Core/FileSystem.cpp
)

add_library(Hazel INTERFACE)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
#  ${Hazel_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/Sandbox/
#)
#
#add_executable(Sandbox.exe
#  ${Hazel_SOURCE_DIR}/Sandbox/src/SandboxApp.cpp
#  ${Hazel_SOURCE_DIR}/Sandbox/src/Sandbox2D.cpp
#  ${Hazel_SOURCE_DIR}/Sandbox/src/ExampleLayer.cpp
#)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
  ${Hazel_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/Hazelnut/
)

add_executable(Hazelnut.exe
  ${Hazel_SOURCE_DIR}/Hazelnut/src/Panels/ContentBrowserPanel.cpp
  ${Hazel_SOURCE_DIR}/Hazelnut/src/Panels/SceneHierarchyPanel.cpp
  ${Hazel_SOURCE_DIR}/Hazelnut/src/EditorLayer.cpp
  ${Hazel_SOURCE_DIR}/Hazelnut/src/HazelnutApp.cpp
)

########################################################################
# Link libraries together
target_link_libraries(HZ_Hazel_Project
  yaml-cpp
)

target_link_libraries(HZ_Hazel_Scripting
  HZ_Hazel_Core
  PkgConfig::MONO_PKG
)

target_link_libraries(HZ_Platform_OpenGL
  Vulkan::Vulkan shaderc_combined_lib spirv-cross
)

target_link_libraries(HZ_Hazel_Core
  HZ_Platform_Linux HZ_Hazel_ImGui HZ_Hazel_Scripting
)

target_link_libraries(HZ_Platform_Linux
  HZ_Platform_OpenGL HZ_Hazel_Renderer
  PkgConfig::GTKMM_PKG
)

target_link_libraries(HZ_Hazel_Renderer
  HZ_Platform_OpenGL HZ_Platform_Linux HZ_Hazel_Core
)

target_link_libraries(HZ_Hazel_Scene
  HZ_Hazel_Core HZ_Hazel_Project
  box2d
)

target_link_libraries(Hazel INTERFACE
  HZ_Hazel_Core HZ_Platform_Linux HZ_Platform_OpenGL HZ_Hazel_Renderer HZ_Hazel_ImGui HZ_Hazel_Scene HZ_Hazel_Math HZ_Hazel_Scripting HZ_Hazel_Project
  glfw OpenGL::GL glad imgui glm stb_image yaml-cpp ImGuizmo box2d Vulkan::Vulkan shaderc_combined_lib spirv-cross
)

#target_link_libraries(Sandbox.exe
#  Hazel
#)

target_link_libraries(Hazelnut.exe
  Hazel
)
