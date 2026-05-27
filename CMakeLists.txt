# Project Info

cmake_minimum_required(VERSION 3.14)
project(spiral-arm)

# Setup Varibles

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

include(FetchContent)
set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/vendor")

# SDL3

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG origin/main
    OVERRIDE_FIND_PACKAGE
)

FetchContent_MakeAvailable(SDL3)

# SDL3_image

FetchContent_Declare(
    SDL3_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG origin/main
    OVERRIDE_FIND_PACKAGE
)

FetchContent_MakeAvailable(SDL3_image)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

# Sources

add_library(spiral-arm STATIC
    src/spiral_camera.cpp
    src/spiral_graphics.cpp
    src/spiral_scene.cpp
    src/spiral_ui.cpp
    src/spiral_window.cpp
    src/spiral_main.cpp
)

# Library linking

target_link_libraries(spiral-arm PRIVATE SDL3::SDL3-static SDL3_image::SDL3_image-static)

# Includes

target_include_directories(spiral-arm PUBLIC
    include
)

add_library(spiral-arm::spiral-arm ALIAS spiral-arm)