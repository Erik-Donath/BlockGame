cmake_minimum_required(VERSION 3.28)
project(BlockGame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW lib only" FORCE)

add_executable(BlockGame
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
        src/gfx/Texture.cpp
        src/gfx/Texture.h
)

target_compile_definitions(BlockGame PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/res")
#target_compile_definitions(BlockGame PUBLIC RESOURCES_PATH="./res")

#Include Libaries
set(Include_DIR "${PROJECT_SOURCE_DIR}/include")

# GLFW
add_subdirectory("${Include_DIR}/glfw")
target_link_libraries(BlockGame glfw)

# OpenGL
# find_package(OpenGL REQUIRED)
# target_link_libraries(HelloCMake OpenGL::GL)

# GLAD
add_subdirectory("${Include_DIR}/glad")
target_link_libraries(BlockGame glad)

# STB
add_subdirectory("${Include_DIR}/stb")
target_link_libraries(BlockGame stb)
