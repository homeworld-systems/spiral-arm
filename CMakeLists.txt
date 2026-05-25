cmake_minimum_required(VERSION 3.14)
project(spiral-arm)

add_library(spiral-arm STATIC
    src/spiral_camera.cpp
    src/spiral_graphics.cpp
    src/spiral_scene.cpp
    src/spiral_ui.cpp
    src/spiral_window.cpp
)

target_include_directories(spiral-arm PUBLIC
    include
)