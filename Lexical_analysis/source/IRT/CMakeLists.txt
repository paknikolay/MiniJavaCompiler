add_library(Irt STATIC IRTNodeBase.cpp IRTExp Statement IRTBuilderVisotor/IRTBuilderVisitor.cpp)

target_include_directories(Irt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(Irt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(CMakeExample::Irt ALIAS Irt)
