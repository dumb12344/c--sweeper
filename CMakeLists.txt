cmake_minimum_required(VERSION 3.10.0)
project(c++sweeper VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDLTTF_VENDORED ON)

add_subdirectory(external/SDL EXCLUDE_FROM_ALL)
add_subdirectory(external/SDL_ttf EXCLUDE_FROM_ALL)
add_subdirectory(external/SDL_image EXCLUDE_FROM_ALL)

if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html" CACHE INTERNAL "")
endif()

add_executable(
    c++sweeper src/main.cpp
    src/graphics/drawboard.cpp
    src/graphics/drawboard.h
    src/constants.h
    src/tiles.cpp
    src/tiles.h
    src/gamemanager.cpp
    src/gamemanager.h
    src/graphics/cache.cpp
    src/graphics/cache.h
)

target_compile_options(c++sweeper PRIVATE $<$<CXX_COMPILER_ID:Clang>:-Wno-c23-extensions>)

target_link_libraries(c++sweeper PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf)