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
        # Entry
        src/Defines.h
        src/main.cpp

        # Application
        src/Application/Application.h
        src/Application/Application.cpp
        src/Application/Window.h
        src/Application/Window.cpp
        src/Application/Input.h
        src/Application/ImGUI.h
        src/Application/ImGUI.cpp
        src/Application/Debug.h
        src/Application/Debug.cpp

        # Rendering
        src/Rendering/GL.h
        src/Rendering/GL.cpp
        src/Rendering/VertexBuffer.h
        src/Rendering/IndexBuffer.h
        src/Rendering/VertexArray.h
        src/Rendering/VertexArray.cpp
        src/Rendering/Shader.h
        src/Rendering/Shader.cpp
        src/Rendering/Texture.h
        src/Rendering/Texture.cpp
        src/Rendering/Renderer.h

        # Scene
        src/Scene/Scene.h
        src/Scene/Scene.cpp
        src/Scene/Transform.h
        src/Scene/Transform.cpp

        # Game
        src/Game/MainScene.h
        src/Game/MainScene.cpp
        src/Game/Block.h
        src/Game/Block.cpp

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
