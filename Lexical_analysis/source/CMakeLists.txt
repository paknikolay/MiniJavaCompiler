cmake_minimum_required(VERSION 3.14)

find_package(FLEX REQUIRED)

# Создаём специальный таргет, который генерирует lex.yy.cc в папке билда
flex_target(flex_scanner scanner.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cc)

configure_file(MiniJavaScanner.h  MiniJavaScanner.h  COPYONLY)

# Сгенерированный файл записывается в переменную FLEX_flex_scanner_OUTPUTS,
# можем использовать её, как исходный файл
add_library(miniJavaScanner STATIC MiniJavaScanner.cpp ${FLEX_flex_scanner_OUTPUTS})

add_library(CMakeExample::miniJavaScanner ALIAS miniJavaScanner)
