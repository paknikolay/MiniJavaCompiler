#pragma once

using std::ifstream;
using std::ofstream;
using std::cout;
using std::string;

std::string readFile(std::string fileName) {
    ifstream file(fileName);
    string file_graph;
    file.seekg(0, std::ios::end);
    file_graph.reserve(file.tellg());
    file.seekg(0, std::ios::beg);

    file_graph.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    file.close();

    return file_graph;
}

#include "MiniJavaScanner.h"

void test(const string& filename, bool is_null=false){
    try {
        string path = "./positive_tests/";
        path.append(filename);

        ifstream testin(path);

        MiniJavaScanner lexer(testin);

        std::shared_ptr<BaseNode> res;
        yy::parser parser(lexer, res);


        if (parser.parse()) {
        }
        assert((res.get() == nullptr) ==  is_null);

    } catch (...) {
    }
}