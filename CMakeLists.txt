cmake_minimum_required(VERSION 2.6)
project(datareader)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

add_subdirectory(pngwriter)

add_executable(datareader main.cpp filereader.cpp filereaderBebop.cpp filereaderBAfilter.cpp)

install(TARGETS datareader RUNTIME DESTINATION bin)

target_link_libraries(datareader png_writer -lpng -lz)
