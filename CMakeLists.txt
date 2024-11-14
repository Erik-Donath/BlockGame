cmake_minimum_required(VERSION 3.28)
project(BlockGame)

### Setup
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/out/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/arc)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW lib only" FORCE)

### Project Architecture
add_executable(BlockGame
        src/main.cpp

        src/Window.h src/Window.cpp
        src/Application.h src/Application.cpp
        src/GUI.h src/GUI.cpp

        src/Buffer.h
        src/GL.h src/GL.cpp
        src/Shader.h src/Shader.cpp
        src/VertexArray.h src/VertexArray.cpp

        src/Game/Util.h
        src/Game/Test.h src/Game/Test.cpp
        src/Game/BlockGame.h src/Game/BlockGame.cpp

        src/Game/Camera.h src/Game/Camera.cpp
)

# copy assets
add_custom_target(Copy_Assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res
        COMMENT "Copying assets")

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