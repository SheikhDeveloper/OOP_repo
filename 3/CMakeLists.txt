cmake_minimum_required(VERSION 3.16)

project(lab3 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-Werror -Wall -Wextra  -Wpedantic  -Wcast-align  -Wcast-qual  -Wconversion  -Wctor-dtor-privacy -Wsign-conversion  -Wsign-promo") 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wenum-compare  -Wfloat-equal  -Wnon-virtual-dtor  -Wold-style-cast  -Woverloaded-virtual  -Wredundant-decls")

option(ASAN "Turn on address and undefined behavior sanitizer" ON)
option(ASAN "Turn off address and undefined behavior sanitizer" OFF)

option(DEBUG_FLAG "Add debugger flag to project compilation" ON)
option(DEBUG_FLAG "Compile without debugger flag" OFF)

option(GET_COVERAGE "Run tests with code coverage" ON)
option(GET_COVERAGE "Run tests without code coverage" OFF)

if(DEBUG_FLAG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif(DEBUG_FLAG)

if (ASAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined")
endif(ASAN)

if(GET_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
endif(GET_COVERAGE)

add_library(weaponry lib/headers/weaponry.h lib/src/weaponry.cc)
add_library(plane lib/headers/plane.h lib/src/plane.cc)
add_library(battleship lib/headers/battleship.h lib/headers/aircraft_carrier.h lib/headers/covering_ship.h  
    lib/headers/aircraft_cruiser.h lib/headers/captain_info.h lib/src/battleship.cc lib/src/aircraft_carrier.cc lib/src/covering_ship.cc lib/src/aircraft_cruiser.cc lib/src/captain_info.cc)
add_library(battleship_group lib/headers/battleship_group.h lib/src/battleship_group.cc)
add_library(plane_group lib/headers/plane_group.h lib/src/plane_group.cc)

add_subdirectory(test)
