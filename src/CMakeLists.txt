cmake_minimum_required(VERSION 3.10)
project(raytracer-challenge)

add_library(raytracer SHARED
    common.h
    Camera.cpp
    Camera.h
    Canvas.cpp
    Canvas.h
    Color.h
    Intersection.cpp
    Intersection.h
    Material.cpp
    Material.h
    Matrix.h
    Plane.h
    Plane.cpp
    PointLight.h
    Ray.h
    Shape.cpp
    Shape.h
    Sphere.cpp
    Sphere.h
    Transformations.h
    Tuple.h
    World.cpp
    World.h
)
set_target_properties(raytracer PROPERTIES LINKER_LANGUAGE CXX)
