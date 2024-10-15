cmake_minimum_required(VERSION 3.16)

project(lab2 VERSION 1.0 LANGUAGES CXX)

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

add_library(cocktail_card lib/cocktail_card.h lib/cocktail_card.cc)
add_library(cocktail lib/cocktail.h lib/cocktail.cc)

add_subdirectory(test)
