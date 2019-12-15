add_library(SymbolTable STATIC SymbolTable.cpp
        )


target_include_directories(SymbolTable PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(CMakeExample::SymbolTable ALIAS SymbolTable)
