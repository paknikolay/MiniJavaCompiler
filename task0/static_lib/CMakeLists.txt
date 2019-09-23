add_library(static_lib STATIC
        Forest.cpp)

add_library(task0::static_lib ALIAS static_lib)
