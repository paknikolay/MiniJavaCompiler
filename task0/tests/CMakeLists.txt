find_package(GTest REQUIRED)

add_executable(tests tests.cpp)

target_include_directories(tests
        PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(tests
        PRIVATE static_lib GTest::Main)
