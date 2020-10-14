cmake_minimum_required(VERSION 3.10)
project(raytracer-challenge)

add_library(raytracer SHARED
    common.h
    Camera.cpp
    Camera.h
    Canvas.cpp
    Canvas.h
    CheckerPattern.cpp
    CheckerPattern.h
    Color.h
    GradientPattern.cpp
    GradientPattern.h
    Intersection.cpp
    Intersection.h
    Material.cpp
    Material.h
    Matrix.h
    Pattern.cpp
    Pattern.h
    Plane.cpp
    Plane.h
    PointLight.h
    Ray.h
    RingPattern.cpp
    RingPattern.h
    Shape.cpp
    Shape.h
    Sphere.cpp
    Sphere.h
    StripePattern.cpp
    StripePattern.h
    Transformations.h
    Tuple.h
    World.cpp
    World.h
)
set_target_properties(raytracer PROPERTIES LINKER_LANGUAGE CXX)
