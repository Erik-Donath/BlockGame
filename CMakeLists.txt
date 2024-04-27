cmake_minimum_required(VERSION 3.28)
project(BlockGame)

### Setup
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/lib)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW lib only" FORCE)

### Project Architecture
add_executable(BlockGame
        # Application
        src/main.cpp

        # GFX
        src/Rendering/GFX.h
        src/Rendering/Base.h
        src/Rendering/gfx/GL.h
        src/Rendering/gfx/GL.cpp
        src/Rendering/gfx/GLBuffer.h
        src/Rendering/gfx/IndexBuffer.h
        src/Rendering/gfx/VertexBuffer.h
        src/Rendering/gfx/VertexArray.h
        src/Rendering/gfx/VertexArray.cpp
        src/Rendering/gfx/VertexBufferLayout.h
        src/Rendering/gfx/Texture.h
        src/Rendering/gfx/Texture.cpp
        src/Rendering/gfx/Shader.h
        src/Rendering/gfx/Shader.cpp

        src/Rendering/base/Renderer.h
        src/Rendering/base/Renderer.cpp
        src/Rendering/base/Window.h
        src/Rendering/base/Window.cpp
        src/Rendering/base/ImGUI.h
        src/Defines.h
        src/Application/App.cpp
        src/Application/App.h
        src/Rendering/base/ImGUI.cpp
        src/Application/Scene.h
        src/Game/MainScene.cpp
        src/Game/MainScene.h
        src/Application/Scene.cpp
)

# Resource directory
target_compile_definitions(BlockGame PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/res")
#target_compile_definitions(BlockGame PUBLIC RESOURCES_PATH="./res")

###Include Libaries
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

# GLM
add_subdirectory("${Include_DIR}/glm")
target_link_libraries(BlockGame glm)

# DEAR IMGUI
add_subdirectory("${Include_DIR}/imgui")
target_link_libraries(BlockGame imgui)
