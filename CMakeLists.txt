cmake_minimum_required(VERSION 3.12)
project(mini_java_compiler)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Lexical_analysis/source)

add_executable(mini_java_compiler main.cpp Lexical_analysis/source/DotVisitor.cpp)

target_link_libraries (mini_java_compiler PRIVATE miniJavaScanner)
configure_file(${CMAKE_SOURCE_DIR}/someTestForDebug someTestForDebug COPYONLY)
if(BUILD_TESTS_LEXER)
    enable_testing()
        find_program(SHELL sh REQUIRED)
        add_test("Test1" ${SHELL} $CMAKE_CURRENT_SOURCE_DIR}/source.sh)
    add_subdirectory(Lexical_analysis/tests)
endif()