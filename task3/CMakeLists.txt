cmake_minimum_required(VERSION 2.6)

#project(rational)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#set(LIB_FILES rational.h)
add_library(rational STATIC rational.h)

#set(SOURCE_FILES testt.cpp)
add_executable(testt testt.cpp)

#install(TARGETS rational DESTINATION lib)
install(FILES rational.h DESTINATION include)