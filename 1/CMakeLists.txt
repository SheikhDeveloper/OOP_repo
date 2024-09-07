cmake_minimum_required(VERSION 3.16)

project(lab1 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-Werror -Wall -Wextra  -Wpedantic  -Wcast-align  -Wcast-qual  -Wconversion  -Wctor-dtor-privacy -Wsign-conversion  -Wsign-promo") 
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -Wenum-compare  -Wfloat-equal  -Wnon-virtual-dtor  -Wold-style-cast  -Woverloaded-virtual  -Wredundant-decls")

add_executable(lab1 main.cc)

add_library(encoder encoder.hpp encoder.cc)

target_link_libraries(lab1 encoder)

