cmake_minimum_required(VERSION 3.10)

project(raytracer-challenge)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

include_directories(
    "${PROJECT_SOURCE_DIR}/src"
)

enable_testing()

add_subdirectory(apps)
add_subdirectory(src)
add_subdirectory(test)
