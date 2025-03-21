cmake_minimum_required(VERSION 3.10.0)

project(coconut C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Wconversion -Wpedantic)

file(GLOB SOURCES
        src/*.c
        src/display/*.c
        src/errors/*.c
        src/utils/*.c)

add_executable(coconut ${SOURCES})

target_include_directories(coconut PRIVATE include)

