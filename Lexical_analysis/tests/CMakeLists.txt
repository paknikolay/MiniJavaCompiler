cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

add_executable(tests tests.cpp)

target_include_directories(tests
        PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(tests
        PRIVATE miniJavaScanner
        PRIVATE GTest::Main
        )

configure_file(${CMAKE_SOURCE_DIR}/Lexical_analysis/tests/test1.in test1.in COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/Lexical_analysis/tests/test1.out test1.out COPYONLY)