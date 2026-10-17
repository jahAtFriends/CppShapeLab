cmake_minimum_required(VERSION 3.20)
project(shapeLab CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(shapes main.cpp PlaneVector.cpp Polygon.cpp SimplePolygon.cpp Rectangle.cpp Circle.cpp)
target_compile_options(shapes PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)