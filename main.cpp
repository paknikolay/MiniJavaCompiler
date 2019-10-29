#include "Lexical_analysis/source/MiniJavaScanner.h"
#include "Statement/Statements.h"
#include <fstream>

#include "Visitor.h"

using std::ifstream;
using std::ofstream;
int main() {
    try {

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
        Visitor visitor;
        visitor.DrawTree(res, "trr.dot");
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