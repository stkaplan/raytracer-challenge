cmake_minimum_required(VERSION 3.10)
project(raytracer-challenge)

set(APPS
    cannon
    clock
    sphere
)
foreach(app ${APPS})
    add_executable(${app} ${app}/main.cpp)
    target_link_libraries(${app} PRIVATE raytracer)
    add_test(NAME ${app}_run COMMAND ${app})
    add_test(NAME ${app}_check_output COMMAND diff image.ppm ${app}.ppm)

    add_custom_command(TARGET ${app} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/test/${app}.ppm
            ${CMAKE_CURRENT_BINARY_DIR}/${app}.ppm
        MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/test/${app}.ppm)
endforeach()
