#include <gtest/gtest.h>

#include "../source/MiniJavaScanner.h"
#include "test_funcs.h"

DotVisitor visitor;

TEST(dot_visitor_tests, test1) {
    test("BinarySearch.java", &visitor);
}

TEST(dot_visitor_tests, test2) {
    test("BinaryTree.java", &visitor);
}

TEST(dot_visitor_tests, test3) {
    test("BubbleSort.java", &visitor);
}

TEST(dot_visitor_tests, test4) {
    test("Factorial.java", &visitor);
}

TEST(dot_visitor_tests, test5) {
    test("LinearSearch.java", &visitor);
}

TEST(dot_visitor_tests, test6) {
    test("LinkedList.java", &visitor);
}

TEST(dot_visitor_tests, test8) {
    test("QuickSort.java", &visitor);
}

TEST(dot_visitor_tests, test9) {
    test("QuickSort.java", &visitor);
}
