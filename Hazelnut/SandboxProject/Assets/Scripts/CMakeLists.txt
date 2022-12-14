cmake_minimum_required(VERSION 3.20)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  execute_process(COMMAND bash ${Hazel_SOURCE_DIR}/Hazelnut/SandboxProject/Assets/Scripts/compileDebug.sh
    WORKING_DIRECTORY ${Hazel_SOURCE_DIR}/Hazelnut/SandboxProject/Assets/Scripts
  )
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  execute_process(COMMAND bash ${Hazel_SOURCE_DIR}/Hazelnut/SandboxProject/Assets/Scripts/compileRelease.sh
    WORKING_DIRECTORY ${Hazel_SOURCE_DIR}/Hazelnut/SandboxProject/Assets/Scripts
  )
endif()
