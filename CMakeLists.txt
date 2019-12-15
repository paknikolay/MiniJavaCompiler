cmake_minimum_required(VERSION 3.12)
project(mini_java_compiler)

set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})


# we use this to get code coverage
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()



add_subdirectory(Lexical_analysis/source)

add_executable(mini_java_compiler main.cpp)

target_link_libraries (mini_java_compiler PRIVATE miniJavaScanner)
configure_file(${CMAKE_SOURCE_DIR}/someTestForDebug someTestForDebug COPYONLY)
if(AST_TESTS)
    include(for_tests_cmake/googletest.cmake)
    fetch_googletest(
            ${PROJECT_SOURCE_DIR}/for_tests_cmake
            ${PROJECT_BINARY_DIR}/googletest
    )

    enable_testing()

    add_subdirectory(Lexical_analysis/tests)
endif()

find_program( MEMORYCHECK_COMMAND valgrind )
set( MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full" )
