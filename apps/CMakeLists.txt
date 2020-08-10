cmake_minimum_required(VERSION 3.10)
project(raytracer-challenge)

add_executable(cannon cannon/main.cpp)
target_link_libraries(cannon PRIVATE raytracer)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test/cannon.ppm
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME cannon_run COMMAND cannon)
add_test(NAME cannon_check_output COMMAND diff image.ppm cannon.ppm)

add_executable(clock clock/main.cpp)
target_link_libraries(clock PRIVATE raytracer)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test/clock.ppm
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME clock_run COMMAND clock)
add_test(NAME clock_check_output COMMAND diff image.ppm clock.ppm)

add_executable(sphere sphere/main.cpp)
target_link_libraries(sphere PRIVATE raytracer)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test/sphere.ppm
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME sphere_run COMMAND sphere)
add_test(NAME sphere_check_output COMMAND diff image.ppm sphere.ppm)
