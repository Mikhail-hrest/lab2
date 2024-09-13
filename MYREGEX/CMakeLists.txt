cmake_minimum_required(VERSION 3.16)
project(MYREGEX)
#include_directories(../"DFA")
#include_directories(../"NFA")
#include_directories(../"Tree")

set(CMAKE_CXX_STANDART 20)
if(CMAKE_COMPILER_IS_GNUCXX)
        message(STATUS "GCC detected, adding compile flags")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -pedantic -Wall -Wextra")
endif(CMAKE_COMPILER_IS_GNUCXX)
add_library(MYREGEX MYREGEX.h MYREGEX.cpp)





