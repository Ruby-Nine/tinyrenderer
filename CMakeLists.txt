cmake_minimum_required(VERSION 3.15.1)

project(tinyrenderer)

add_compile_options(-Wall -O3 -std=c++17)

# include_directories(${CMAKE_SOURCE_DIR})

add_executable(tinyrenderer main.cpp global.hpp tgaimage.hpp tgaimage.cpp rasterizer.hpp rasterizer.cpp model.hpp model.cpp geometry.hpp)



