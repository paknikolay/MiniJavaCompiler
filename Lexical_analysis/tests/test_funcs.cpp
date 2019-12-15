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

std::vector<std::string> badFiles{
                                  "negative_tests/LC_1.java",
                                  "negative_tests/TC_1a.java",
                                  "negative_tests/TC_2.java",
                                  "negative_tests/TC_2a.java",
                                  "negative_tests/TC_3a(1).java",
                                  "negative_tests/TC_3a(2).java",
                                  "negative_tests/TC_3a.java",
                                  "negative_tests/TC_3b.java",
                                  "negative_tests/TC_4a.java",
                                  "negative_tests/TC_4b.java",
                                  "negative_tests/TC_5a.java",
                                  "negative_tests/TC_6a.java",
                                  "negative_tests/TC_7b.java",
                                  "negative_tests/TC_7c.java",
                                  "negative_tests/TC_8a.java",
                                  "negative_tests/TC_9a.java",
                                  "negative_tests/TC_9a_2.java",
                                  "negative_tests/TC_11a.java",
                                  "negative_tests/TC_12b.java",
                                  "negative_tests/TC_13_a.java",
                                  "negative_tests/TC_13b.java",
                                  "negative_tests/TC_13c.java",
                                  "negative_tests/TC_bonus1.java"

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