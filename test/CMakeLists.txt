cmake_minimum_required(VERSION 3.10)
project(raytracer-challenge)

set(TEST_PROGS
    Test_Camera
    Test_Canvas
    Test_Color
    Test_Intersection
    Test_Material
    Test_Matrix
    Test_Pattern
    Test_Plane
    Test_PointLight
    Test_Ray
    Test_Shape
    Test_Sphere
    Test_Transformations
    Test_Tuple
    Test_World
)

foreach(test_prog ${TEST_PROGS})
    add_executable(${test_prog} ${test_prog}.cpp main.cpp)
    target_link_libraries(${test_prog} raytracer)
    add_test(NAME ${test_prog} COMMAND ${test_prog})
endforeach()
