cmake_minimum_required(VERSION 3.14)
project(spiral-arm)

file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp")

add_library(spiral-arm STATIC ${SOURCES})

target_include_directories(spiral-arm PUBLIC "include/*.cpp" "include/*/*.cpp")