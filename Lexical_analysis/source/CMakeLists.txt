find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)


# Создаём специальный таргет, который генерирует lex.yy.cc в папке билда
flex_target(flex_scanner scanner.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cc)
# target_include_directories(flex_scanner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Lexical_analysis/source)

bison_target(bison_parser parser.yy ${CMAKE_CURRENT_BINARY_DIR}/parser.cc COMPILE_FLAGS -v)

# target_include_directories(bison_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Lexical_analysis/source)
#configure_file(MiniJavaScanner.h  MiniJavaScanner.h  COPYONLY)

# Сгенерированный файл записывается в переменную FLEX_flex_scanner_OUTPUTS,
# можем использовать её, как исходный файл
add_subdirectory(Ast)

add_subdirectory(SymbolTable)

add_subdirectory(IRT)

add_flex_bison_dependency(flex_scanner bison_parser)

add_library(miniJavaScanner STATIC ${FLEX_flex_scanner_OUTPUTS}
            ${BISON_bison_parser_OUTPUTS} MiniJavaScanner.cpp DotVisitor.cpp SymbolTableVisitor.cpp)

target_link_libraries(miniJavaScanner
        PUBLIC Ast PUBLIC Irt
)

target_include_directories(miniJavaScanner PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(miniJavaScanner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(CMakeExample::miniJavaScanner ALIAS miniJavaScanner )
