cmake_minimum_required(VERSION 3.16)
project(Hazel)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(HZ_DEBUG)

include_directories(vendor/spdlog/include)
include_directories(vendor/Glad/include)
include_directories(vendor/GLFW/include)
include_directories(vendor/imgui)
include_directories(vendor/stb_image)
include_directories(vendor/glm)

add_subdirectory(vendor/glm)
add_subdirectory(vendor/GLFW)

set(IMGUI_SRC
        vendor/imgui/imgui.h
        vendor/imgui/imgui.cpp
        vendor/imgui/imgui_widgets.cpp
        vendor/imgui/imgui_demo.cpp
        vendor/imgui/imgui_draw.cpp)

set(STBIMG_SRC
        vendor/stb_image/stb_image.cpp)

set(GLAD_SRC
        vendor/Glad/src/glad.c)

set(SOURCES
        src/Hazel/Core/Application.cpp
        src/Hazel/Core/Application.h
        src/Hazel/Core/Core.h
        src/Hazel/Core/EntryPoint.h
        src/Hazel/Core/Input.cpp
        src/Hazel/Core/Input.h
        src/Hazel/Core/KeyCodes.h
        src/Hazel/Core/Layer.cpp
        src/Hazel/Core/Layer.h
        src/Hazel/Core/LayerStack.cpp
        src/Hazel/Core/LayerStack.h
        src/Hazel/Core/Log.cpp
        src/Hazel/Core/Log.h
        src/Hazel/Core/MouseCodes.h
        src/Hazel/Core/Timestep.h
        src/Hazel/Core/Window.cpp
        src/Hazel/Core/Window.h
        src/Hazel/Debug/Instrumentor.h
        src/Hazel/Events/ApplicationEvent.h
        src/Hazel/Events/Event.h
        src/Hazel/Events/KeyEvent.h
        src/Hazel/Events/MouseEvent.h
        src/Hazel/ImGui/ImGuiBuild.cpp
        src/Hazel/ImGui/ImGuiLayer.cpp
        src/Hazel/ImGui/ImGuiLayer.h
        src/Hazel/Renderer/Buffer.cpp
        src/Hazel/Renderer/Buffer.h
        src/Hazel/Renderer/GraphicsContext.cpp
        src/Hazel/Renderer/GraphicsContext.h
        src/Hazel/Renderer/OrthographicCamera.cpp
        src/Hazel/Renderer/OrthographicCamera.h
        src/Hazel/Renderer/OrthographicCameraController.cpp
        src/Hazel/Renderer/OrthographicCameraController.h
        src/Hazel/Renderer/RenderCommand.cpp
        src/Hazel/Renderer/RenderCommand.h
        src/Hazel/Renderer/Renderer.cpp
        src/Hazel/Renderer/Renderer.h
        src/Hazel/Renderer/Renderer2D.cpp
        src/Hazel/Renderer/Renderer2D.h
        src/Hazel/Renderer/RendererAPI.cpp
        src/Hazel/Renderer/RendererAPI.h
        src/Hazel/Renderer/Shader.cpp
        src/Hazel/Renderer/Shader.h
        src/Hazel/Renderer/Texture.cpp
        src/Hazel/Renderer/Texture.h
        src/Hazel/Renderer/VertexArray.cpp
        src/Hazel/Renderer/VertexArray.h
        src/Platform/OpenGL/OpenGLBuffer.cpp
        src/Platform/OpenGL/OpenGLBuffer.h
        src/Platform/OpenGL/OpenGLContext.cpp
        src/Platform/OpenGL/OpenGLContext.h
        src/Platform/OpenGL/OpenGLRendererAPI.cpp
        src/Platform/OpenGL/OpenGLRendererAPI.h
        src/Platform/OpenGL/OpenGLShader.cpp
        src/Platform/OpenGL/OpenGLShader.h
        src/Platform/OpenGL/OpenGLTexture.cpp
        src/Platform/OpenGL/OpenGLTexture.h
        src/Platform/OpenGL/OpenGLVertexArray.cpp
        src/Platform/OpenGL/OpenGLVertexArray.h
        src/Platform/Windows/WindowsInput.cpp
        src/Platform/Windows/WindowsInput.h
        src/Platform/Windows/WindowsWindow.cpp
        src/Platform/Windows/WindowsWindow.h
        src/Hazel.h
        src/hzpch.cpp
        src/hzpch.h)

include_directories(src)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${IMGUI_SRC} ${GLAD_SRC} ${STBIMG_SRC})

target_link_libraries(${PROJECT_NAME} glfw)