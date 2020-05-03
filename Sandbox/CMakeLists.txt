cmake_minimum_required(VERSION 3.16)
project(Sandbox)

set(CMAKE_CXX_STANDARD 17)

include_directories(../Hazel/vendor/spdlog/include)
include_directories(../Hazel/vendor/Glad/include)
include_directories(../Hazel/vendor/GLFW/include)
include_directories(../Hazel/vendor/imgui)
include_directories(../Hazel/vendor/stb_image)
include_directories(../Hazel/vendor/glm)

include_directories(../Hazel/src)

set(SOURCES
        src/ExampleLayer.cpp
        src/ExampleLayer.h
        src/Sandbox2D.cpp
        src/Sandbox2D.h
        src/SandboxApp.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} Hazel)