cmake_minimum_required(VERSION 3.28)
project(HelloCMake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")

#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug$<$<CONFIG:Debug>:Debug>")
#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW lib only" FORCE)

add_executable(HelloCMake
        # Application
        src/main.cpp

        # GFX
        src/gfx/GL.h
        src/gfx/GL.cpp
        src/gfx/Window.h
        src/gfx/Window.cpp
        src/gfx/GLBuffer.h
        src/gfx/VertexArray.h
        src/gfx/VertexArray.cpp
        src/gfx/VertexBufferLayout.h
        src/gfx/Shader.h
        src/gfx/Shader.cpp

        # Base
        src/base/GFX.h
        src/base/Renderer.h
        src/base/Renderer.cpp
)

#Include Libaries
set(Include_DIR "${PROJECT_SOURCE_DIR}/include")

# GLFW
add_subdirectory("${Include_DIR}/glfw-3.4")
target_link_libraries(HelloCMake glfw)

# GLAD
add_subdirectory("${Include_DIR}/glad")
target_link_libraries(HelloCMake glad)

# OpenGL
# find_package(OpenGL REQUIRED)
# target_link_libraries(HelloCMake OpenGL::GL)
