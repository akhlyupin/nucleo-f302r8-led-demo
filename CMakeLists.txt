cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

project(nucleo-f302r8-research)
enable_language(C CXX ASM)

add_subdirectory(cubemx)
add_subdirectory(demo-app)
add_subdirectory(snake-app)