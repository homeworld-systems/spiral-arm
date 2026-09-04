# Project Info

cmake_minimum_required(VERSION 3.14)
project(spiral-arm)

# Setup Variables

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
    spiral-arm/src/spiral_main.cpp
    spiral-arm/src/spiral_scene.cpp
)

# Library linking

target_link_libraries(spiral-arm PRIVATE SDL3::SDL3-static SDL3_image::SDL3_image-static)

# Includes

target_include_directories(spiral-arm PUBLIC
    spiral-arm/include
)

target_include_directories(spiral-arm PUBLIC
    ${CMAKE_SOURCE_DIR}/vendor/sdl3-src/include
)

add_library(spiral-arm::spiral-arm ALIAS spiral-arm)

# Testing

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    option(SPIRAL_ARM_TEST "Spiral Arm tests" ON)
else()
    option(SPIRAL_ARM_TEST "Spiral Arm tests" OFF)
endif()

if (SPIRAL_ARM_TEST)

    if (WIN32)
        add_executable(spiral_arm_test WIN32 test/main.cpp)
    else()
        add_executable(spiral_arm_test test/main.cpp)
    endif()

    set_target_properties(spiral_arm_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../dest")

    target_include_directories(spiral_arm_test PUBLIC "test/include")

    # Linking main

    target_link_libraries(spiral_arm_test PUBLIC spiral-arm::spiral-arm)

endif()