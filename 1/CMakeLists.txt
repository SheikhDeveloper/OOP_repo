cmake_minimum_required(VERSION 3.16)

project(lab1 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-Werror -Wall -Wextra  -Wpedantic  -Wcast-align  -Wcast-qual  -Wconversion  -Wctor-dtor-privacy -Wsign-conversion  -Wsign-promo") 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wenum-compare  -Wfloat-equal  -Wnon-virtual-dtor  -Wold-style-cast  -Woverloaded-virtual  -Wredundant-decls")

option(ASAN "Turn on address and undefined behavior sanitizer" ON)
option(ASAN "Turn off address and undefined behavior sanitizer" OFF)

option(DEBUG_FLAG "Add debugger flag to project compilation" ON)
option(DEBUG_FLAG "Compile without debugger flag" OFF)

if(DEBUG_FLAG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif(DEBUG_FLAG)

if (ASAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined")
endif(ASAN)

add_executable(lab1 main.cc)

add_library(encoder lib/encoder.hpp lib/encoder.cc)
add_library(utils lib/utils.hpp)
set_target_properties(utils PROPERTIES LINKER_LANGUAGE CXX)
add_library(dialogue_funcs lib/dialogue_funcs.hpp lib/dialogue_funcs.cc)

target_link_libraries(dialogue_funcs encoder utils)
target_link_libraries(lab1 dialogue_funcs)
