cmake_minimum_required(VERSION 3.5.1)

project(clara)

add_compile_options(-Wall -std=c++11)

add_subdirectory(src)

add_subdirectory(thirdparty/catch)
add_subdirectory(tests)

