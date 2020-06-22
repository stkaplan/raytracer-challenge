cmake_minimum_required(VERSION 3.10)
project(raytracer-challenge)

enable_testing()

set(TEST_PROGS Test_Canvas Test_Color Test_Tuple)

foreach(test_prog ${TEST_PROGS})
    add_executable(${test_prog} ${test_prog}.cpp main.cpp)
    target_link_libraries(${test_prog} raytracer)
endforeach()
