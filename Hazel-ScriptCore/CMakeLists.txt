cmake_minimum_required(VERSION 3.20)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  execute_process(COMMAND bash ${Hazel_SOURCE_DIR}/Hazel-ScriptCore/compileDebug.sh
    WORKING_DIRECTORY ${Hazel_SOURCE_DIR}/Hazel-ScriptCore
  )
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  execute_process(COMMAND bash ${Hazel_SOURCE_DIR}/Hazel-ScriptCore/compileRelease.sh
    WORKING_DIRECTORY ${Hazel_SOURCE_DIR}/Hazel-ScriptCore
  )
endif()
