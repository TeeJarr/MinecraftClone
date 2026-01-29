cmake_minimum_required(VERSION 4.1.2)
project(MinecraftClone)

set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCES src/*.cpp)

find_package(raylib)

add_executable(${PROJECT_NAME} ${SOURCES}
        src/main.cpp
        src/Engine/Engine.cpp
        include/Engine/Engine.h
        src/Player.cpp
        include/Player.hpp
        src/Engine/Renderer.cpp
        include/Engine/Renderer.hpp
        include/Engine/Settings.hpp
        include/World/Block.hpp
        src/World/Chunk.cpp
        include/World/Chunk.hpp
)
target_link_libraries(${PROJECT_NAME} PUBLIC raylib)
target_include_directories(${PROJECT_NAME} PUBLIC include)
