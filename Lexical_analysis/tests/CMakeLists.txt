cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

add_executable(ast_tests positive_tests.cpp negative_tests.cpp memleak_tests.cpp test_funcs.cpp dot_visitor_test.cpp IRT_test.cpp)

target_include_directories(ast_tests
        PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(ast_tests
        PRIVATE miniJavaScanner
        PRIVATE GTest::Main
        )

find_program( MEMORYCHECK_COMMAND valgrind )
set( MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full" )



file(COPY ${CMAKE_SOURCE_DIR}/Lexical_analysis/tests/positive_tests DESTINATION  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

file(COPY ${CMAKE_SOURCE_DIR}/Lexical_analysis/tests/positive_tests DESTINATION  ${CMAKE_CURRENT_BINARY_DIR})


file(COPY ${CMAKE_SOURCE_DIR}/Lexical_analysis/tests/negative_tests DESTINATION  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

file(COPY ${CMAKE_SOURCE_DIR}/Lexical_analysis/tests/negative_tests DESTINATION  ${CMAKE_CURRENT_BINARY_DIR})

add_test(
        NAME
        AST_TESTS
        COMMAND
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/ast_tests
)
