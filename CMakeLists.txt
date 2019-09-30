cmake_minimum_required(VERSION 3.14)
project(mini_java_compiler)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Lexical_analysis/source)

add_executable(mini_java_compiler main.cpp)

target_link_libraries (mini_java_compiler PRIVATE miniJavaScanner)
