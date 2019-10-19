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
/*
TEST(work_check, test1) {

    ifstream in("test1.in");
    ofstream rez_out("test1.rez");

    rez_out << "2ewda";
    MiniJavaScanner lexer(in);
    lexer.switch_streams(in, rez_out);

    lexer.tokenize();
    cout<<"_________\n";

    rez_out.close();
    in.close();

    string test_out = readFile("test1.out");
    string rezult = readFile("test1.rez");


    ASSERT_EQ(rezult, test_out);
}
*/
#include <iostream>

#include "MiniJavaScanner.h"

TEST(work_check, test2) {
    MiniJavaScanner lexer;

    void* result;
    yy::parser parser(lexer);

    try {
        if (parser.parse()) {
            return;
        }
        assert(result != nullptr);
        //result->Print(std::cout);
    } catch (std::exception &e) {
        std::cerr << "\x1B[31m" << e.what() << "\x1B[0m" << std::endl;
    }
    return;
}