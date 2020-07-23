cmake_minimum_required(VERSION 3.10)
project(raytracer-challenge)

add_executable(cannon cannon/main.cpp)
target_link_libraries(cannon PRIVATE raytracer)

add_executable(clock clock/main.cpp)
target_link_libraries(clock PRIVATE raytracer)
