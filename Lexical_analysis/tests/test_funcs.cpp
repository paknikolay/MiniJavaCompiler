#include "test_funcs.h"
#include "Visitor.h"

std::vector<std::string> files{"positive_tests/BinarySearch.java",
                               "positive_tests/BinaryTree.java",
                               "positive_tests/BubbleSort.java",
                               "positive_tests/Factorial.java",
                               "positive_tests/LinearSearch.java",
                               "positive_tests/LinkedList.java",
                               "positive_tests/QuickSort.java",
                               "positive_tests/TreeVisitor.java"
                               };

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


void test(const string& filename, bool is_null){
    try {
//TODO добавить проверку визиотором, который проверяет типы
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

void test(const string& filename, DotVisitor* visitor, bool is_null) {
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

        visitor->DrawTree(res, "out");


    } catch (...) {
    }
}