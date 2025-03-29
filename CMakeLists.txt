cmake_minimum_required(VERSION 3.15.1)

project(tinyrenderer)

add_compile_options(-Wall -O0 -std=c++17)

# find_library(Eigen3 REQUIRED)
# include_directories ( ${EIGEN3_INCLUDE_DIRS} )
# Message(STATUS "Eigen3 include dir: ${EIGEN3_INCLUDE_DIR}")

set (MSYS_ROOT_DIR "C:/msys64")
include_directories("${MSYS_ROOT_DIR}/mingw64/include/")


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

file(GLOB SRC_FILES
    "src/*.cpp"
)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(tinyrenderer ${SRC_FILES})
