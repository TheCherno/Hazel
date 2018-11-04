cmake_minimum_required(VERSION 3.8)

# Project
project(Hazel)

# Options
option(HAZEL_BUILD_SANDBOX "Build sandbox application" ON)

# Hazel
add_subdirectory(Hazel)

# Sandbox
if(HAZEL_BUILD_SANDBOX)
    add_subdirectory(Sandbox)
endif()
