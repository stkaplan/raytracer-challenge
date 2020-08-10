cmake_minimum_required(VERSION 3.10)
project(raytracer-challenge)

add_library(raytracer SHARED
    common.h
    Canvas.cpp
    Canvas.h
    Color.h
    Matrix.h
    Ray.h
    Sphere.cpp
    Sphere.h
    Transformations.h
    Tuple.h
)
set_target_properties(raytracer PROPERTIES LINKER_LANGUAGE CXX)
