cmake_minimum_required(VERSION 3.28)
project(BlockGame)

### Setup
set(CMAKE_CXX_STANDARD 20)
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
        src/Engine/App/Application.h
        src/Engine/App/Application.cpp
        src/Engine/App/Window.h
        src/Engine/App/Window.cpp
        src/Engine/App/Input.h
        src/Engine/App/Gui.h
        src/Engine/App/Gui.cpp
        src/Engine/Common/Debug.h
        src/Engine/Common/Debug.cpp

        # Rendering
        src/Engine/Rendering/GL.h
        src/Engine/Rendering/GL.cpp
        src/Engine/Rendering/VertexBuffer.h
        src/Engine/Rendering/IndexBuffer.h
        src/Engine/Rendering/VertexArray.h
        src/Engine/Rendering/VertexArray.cpp
        src/Engine/Rendering/Shader.h
        src/Engine/Rendering/Shader.cpp
        src/Engine/Rendering/Texture.h
        src/Engine/Rendering/Texture.cpp
        src/Engine/Rendering/Renderer.h

        # Scene
        src/Engine/Scene/Scene.h
        src/Engine/Scene/Scene.cpp
        src/Engine/Scene/Transform.h
        src/Engine/Scene/Transform.cpp
        src/Engine/Scene/Camera.h
        src/Engine/Scene/Camera.cpp

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
