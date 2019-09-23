#include <iostream>
#include "Forest.h"


int main() {
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

    FILE* output = fopen("graph.dot", "w");
    forest.Dump(output);

    return 0;
}