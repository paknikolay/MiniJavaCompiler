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