#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <iostream>

#include "../source/MiniJavaScanner.h"
#include "test_funcs.h"
#include "CheckTypeVisitor.h"



class TypeCheckerTests : public testing::TestWithParam<std::string> {


};
INSTANTIATE_TEST_CASE_P(working_checking, TypeCheckerTests, testing::ValuesIn(badFiles.begin(), badFiles.end()));


TEST_P(TypeCheckerTests, working_checking)
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
        return;
    }

    ASSERT_TRUE(false);
}
