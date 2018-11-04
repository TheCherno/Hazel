project(hazel-engine)

# Add sources (only .cpp)
set (SANDBOX_SOURCES
    src/Hazel/Application.cpp
)

# Define shared library
# Create nice looking alias for clients of Hazel to link to 
add_library(${PROJECT_NAME} SHARED ${SANDBOX_SOURCES})
add_library(Hazel::Engine ALIAS ${PROJECT_NAME}) 

# Platform specific preprocessor defines
# PUBLIC  = define is visible to the user of Hazel
# PRIVATE = define is visible Hazel only
if (WIN32)
    target_compile_definitions(${PROJECT_NAME} PUBLIC HZ_PLATFORM_WINDOWS=1)
    target_compile_definitions(${PROJECT_NAME} PRIVATE HZ_BUILD_DLL=1)
endif()
if(APPLE)
    # for MacOS X or iOS, watchOS, tvOS (since 3.10.3)
    target_compile_definitions(${PROJECT_NAME} PUBLIC HZ_PLATFORM_APPLE=1)
endif()
if(UNIX AND NOT APPLE)
    # for Linux, BSD, Solaris, Minix
    target_compile_definitions(${PROJECT_NAME} PUBLIC HZ_PLATFORM_UNIX=1)
endif()

# Set include directories
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src/Hazel)

# Language standard
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Link libraries (e.g. logging)
target_link_libraries(${PROJECT_NAME} 
    # ${CMAKE_THREAD_LIBS_INIT}     # Needed for unix builds to link to pthread
    # LOGGING
)