cmake_minimum_required(VERSION 3.10)
project(raytracer-challenge)

add_library(raytracer SHARED
    common.h
    Tuple.cpp
    Tuple.h
)
