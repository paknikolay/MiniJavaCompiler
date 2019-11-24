add_library(Irt STATIC IRTNodeBase.cpp IRTExp Statement)


target_include_directories(Irt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(CMakeExample::Irt ALIAS Irt)
