cmake_minimum_required(VERSION 3.28)
project(Engine)

add_library(Engine STATIC
        #Entry & Globals
        src/Main.cpp
        include/Define.h
        include/Game.h

        #Application
        include/Application/Window.h
        src/Application/Window.cpp
        include/CustomException.h
)

target_include_directories(Engine PUBLIC include/)

#Include Setup
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW lib only" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW lib only" FORCE)

#Include Libs

## GLFW
add_subdirectory("third-party/glfw")
target_link_libraries(Engine PRIVATE glfw)

## GLAD
add_subdirectory("third-party/glad")
target_link_libraries(Engine PRIVATE glad)
