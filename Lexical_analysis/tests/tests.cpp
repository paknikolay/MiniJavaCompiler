#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <iostream>

#include "../source/MiniJavaScanner.h"

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

#include <iostream>
#include "Lexical_analysis/source/DotVisitor.h"

#include "MiniJavaScanner.h"

TEST(work_check, test2) {
    try {
        ofstream t("outout.out");
        t.close();

        ifstream testin("test1.in");

        MiniJavaScanner lexer(testin);

        std::shared_ptr<BaseNode> res;
        yy::parser parser(lexer, res);


        if (parser.parse()) {
        }
        assert(res.get() != nullptr);

    } catch (...) {
    }

}