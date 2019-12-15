#include <gtest/gtest.h>

#include "../source/MiniJavaScanner.h"
#include "test_funcs.h"


class IRTTest : public testing::TestWithParam<std::string> {


};
INSTANTIATE_TEST_CASE_P(working_checking, IRTTest, testing::ValuesIn(files.begin(), files.end()));


TEST_P(IRTTest, working_checking)
{
    auto file_name = GetParam();
    std::fstream testin(file_name);

    MiniJavaScanner lexer(testin);

    std::shared_ptr<BaseNode> res;
    yy::parser parser(lexer, res);


    if (parser.parse()) {
    }

    auto goal = dynamic_cast<Goal*>(res.get());
    SymbolTableVisitor visitor(goal);

    auto symbolTable = visitor.GetSymbolTable();

    IRTBuilderVisitor builderVisitor(symbolTable);
    builderVisitor.Visit(goal);

    auto trees = builderVisitor.getIrtTrees();

    for (auto treeInfo : trees) {
        ASSERT_NE(treeInfo.irtTree, nullptr);
    }
}