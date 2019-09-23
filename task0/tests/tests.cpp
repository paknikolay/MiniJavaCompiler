#include "../static_lib/Forest.h"

#include <gtest/gtest.h>
#include <fstream>
#include <string>

std::string readFile(std::string fileName) {
    std::ifstream file(fileName);
    std::string file_graph;
    file.seekg(0, std::ios::end);
    file_graph.reserve(file.tellg());
    file.seekg(0, std::ios::beg);

    file_graph.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    file.close();

    return file_graph;
}

TEST(work_check, test1) {
    Forest forest;
    forest.AddVertice("A");
    forest.AddVertice("B");
    forest.AddVertice("C");
    forest.AddVertice("D");
    forest.AddEdge("A", "B");
    forest.AddEdge("A", "C");
    forest.AddEdge("A", "A");
    forest.AddEdge("B", "C");
    forest.AddEdge("C", "A");
    forest.AddEdge("C", "A");

    FILE* output = fopen("graph1.dot", "w");
    forest.Dump(output);
    fclose(output);


    std::string test_graph = readFile("test1.dot");
    std::string out_graph = readFile("graph1.dot");

    ASSERT_EQ(test_graph, out_graph);
}

TEST(work_check, test2) {
    Forest forest;
    forest.AddVertice("A");
    forest.AddVertice("B");
    forest.AddVertice("C");
    forest.AddVertice("D");
    forest.AddVertice("E");
    forest.AddVertice("F");

    forest.AddEdge("A", "B");
    forest.AddEdge("B", "C");

    forest.AddEdge("D", "E");
    forest.AddEdge("E", "F");

    forest.AddEdge("F", "A");
    forest.AddEdge("E", "B");

    FILE* output = fopen("graph2.dot", "w");
    forest.Dump(output);
    fclose(output);


    std::string test_graph = readFile("test2.dot");
    std::string out_graph = readFile("graph2.dot");

    ASSERT_EQ(test_graph, out_graph);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}