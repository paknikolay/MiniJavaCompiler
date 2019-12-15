#include <gtest/gtest.h>
#include <Lexical_analysis/source/CheckTypeVisitor.h>

#include "../source/MiniJavaScanner.h"
#include "test_funcs.h"

TEST(positive_tests, test1) {
    test("BinarySearch.java");
}

TEST(positive_tests, test2) {
    test("BinaryTree.java");
}

TEST(positive_tests, test3) {
    test("BubbleSort.java");
}

TEST(positive_tests, test4) {
    test("Factorial.java");
}

TEST(positive_tests, test5) {
    test("LinearSearch.java");
}

TEST(positive_tests, test6) {
    test("LinkedList.java");
}

TEST(positive_tests, test8) {
    test("QuickSort.java");
}

TEST(positive_tests, test9) {
    test("QuickSort.java");
}



class TypeCheckerTestsPositive : public testing::TestWithParam<std::string> {


};
INSTANTIATE_TEST_CASE_P(working_checking_positive, TypeCheckerTestsPositive, testing::ValuesIn(files.begin(), files.end()));


TEST_P(TypeCheckerTestsPositive, working_checking_positive)
{

    auto file_name = GetParam();
    std::cout<<file_name <<" - filename\n";
    std::fstream testin(file_name);

    MiniJavaScanner lexer(testin);

    std::shared_ptr<BaseNode> res;
    yy::parser parser(lexer, res);

    try {

        if (parser.parse()) {
        }

        auto goal = std::dynamic_pointer_cast<Goal>(res);
        if (goal == nullptr) {
            throw std::runtime_error("lexer/parser error");
        }

        CheckTypeVisitor checkTypeVisitor;
        checkTypeVisitor.CheckTypes(goal);
    } catch (std::exception& exception){
        std::cerr << exception.what();
        ASSERT_TRUE(false);
    }


}
