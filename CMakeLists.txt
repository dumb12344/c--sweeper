cmake_minimum_required(VERSION 3.10.0)
project(c++sweeper VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(SDL3_image REQUIRED CONFIG)
find_package(SDL3_ttf REQUIRED CONFIG)

add_executable(
    c++sweeper src/main.cpp
    src/graphics/drawboard.cpp
    src/graphics/drawboard.h
    src/constants.h
    src/tiles.cpp
    src/tiles.h
    src/gamemanager.cpp
    src/gamemanager.h
)

target_compile_options(c++sweeper PRIVATE $<$<CXX_COMPILER_ID:Clang>:-Wno-c23-extensions>)

target_link_libraries(c++sweeper PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf)