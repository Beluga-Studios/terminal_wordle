cmake_minimum_required(VERSION 3.16)
project(termwordle)

set(CMAKE_CXX_STANDARD 17)

add_executable(termwordle src/main.cpp)
configure_file(src/words.txt words.txt COPYONLY)