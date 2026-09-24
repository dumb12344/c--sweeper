cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(c++sweeper VERSION 0.1.0 LANGUAGES C CXX)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(SDL3_image REQUIRED CONFIG)
find_package(SDL3_ttf REQUIRED CONFIG)

add_executable(
    c++sweeper src/main.cpp
    src/main.hpp
    src/graphics/drawboard.cpp
    src/graphics/drawboard.hpp
    src/constants.hpp
    src/tiles.cpp
    src/tiles.hpp
    src/gamemanager.cpp
    src/gamemanager.hpp
)

target_link_libraries(c++sweeper PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf)