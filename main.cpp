#include "Lexical_analysis/source/MiniJavaScanner.h"
#include "Statement/Statements.h"
#include <fstream>
#include "IRTDotVisitor.h"
#include "SymbolTableVisitor.h"
#include "IRT/IRTBuilderVisotor/IRTBuilderVisitor.h"

#include "DotVisitor.h"

using std::ifstream;
using std::ofstream;
int main() {
    try {
    //    int* unused_var = new int; // to check mem leaks
    /*ofstream out("out");
    ifstream in("in");
    MiniJavaScanner lexer(in);
    lexer.tokenize();
    return 0;*/

    ifstream testin("someTestForDebug");
    MiniJavaScanner lexer(testin);

    std::shared_ptr<BaseNode> res;
    yy::parser parser(lexer, res);


        if (parser.parse()) {
        }
        std::cout <<"\n(((((((((\n"<<(res.get() == nullptr )<< "\n";
        int a = 3;
        int b = 7;
//        DotVisitor visitor;
//        visitor.DrawTree(res, "trr.dot");

        Goal* goal = std::dynamic_pointer_cast<Goal>(res).get();
        SymbolTableVisitor symbolTableVisitor(goal);

        IRTBuilderVisitor irtBuilderVisitor(symbolTableVisitor.GetSymbolTable());
        irtBuilderVisitor.Visit(goal);

        IRTNodeBase *base = irtBuilderVisitor.getIrtTrees()[1].irtTree.get();
//
        ofstream stream("irt.pak");
        auto irtDotVisitor = std::make_shared<IRTDotVisitor>(stream, base);


//        assert(result != nullptr);
        //result->Print(std::cout);
    } catch (...) {
        //std::cerr << "\x1B[31m" << e.what() << "\x1B[0m" << std::endl;
    }
    //auto res2 = dynamic_cast<StatementWhile*>(res.get());
    //auto ggsf = typeid(res.get()).name();


}
/*
#include <iostream>

#include "olc_lexer.h"
#include "tokentree.h"

int main() {
    OlcLex::OlcLexer lexer;

    TreeNodePtr result;
    yy::parser parser(lexer, result);

    try {
        if( parser.parse() ) {
            return 1;
        }
        assert(result != nullptr);
        result->Print(std::cout);
    } catch (std::exception& e) {
        std::cerr << "\x1B[31m" << e.what() << "\x1B[0m" << std::endl;
    }
    return 0;
}*/