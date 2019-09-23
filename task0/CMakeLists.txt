cmake_minimum_required(VERSION 3.8)
project(task0)

# Set required c++ version
set(CMAKE_CXX_STANDARD 17)
# add additional options
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

add_subdirectory(static_lib)

add_executable(task0 main.cpp)
target_link_libraries(task0 PRIVATE static_lib)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

include_directories(static_lib)
