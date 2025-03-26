cmake_minimum_required(VERSION 3.15.1)

project(tinyrenderer)

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(tinyrenderer main.cpp tgaimage.h tgaimage.cpp)
