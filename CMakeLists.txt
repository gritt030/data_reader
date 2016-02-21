cmake_minimum_required(VERSION 2.6)
project(datareader)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

add_executable(datareader main.cpp filereader.cpp filereaderBebop.cpp filereaderBAfilter.cpp)

install(TARGETS datareader RUNTIME DESTINATION bin)
