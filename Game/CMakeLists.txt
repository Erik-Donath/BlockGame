cmake_minimum_required(VERSION 3.28)
project(BlockGame)

### Setup
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/game/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/game/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/game/lib)

### Project Architecture
add_executable(BlockGame
        src/BlockGame.cpp
)

# Add Engine
add_subdirectory("../Engine" "${CMAKE_BINARY_DIR}/engine")
target_link_libraries(BlockGame Engine)
