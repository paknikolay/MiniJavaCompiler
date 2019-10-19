#pragma once

#include <vector>
#include <string>

#if !defined (yyFlexLexerOnce)
#include <FlexLexer.h>
#endif // _!defined (yyFlexLexerOnce)
#include "/home/nikolai/compilers/MiniJavaCompiler/cmake-build-debug/Lexical_analysis/source/parser.hh"

using Token = yy::parser::token::yytokentype;

class MiniJavaScanner : public yyFlexLexer {
private:
    std::vector< std::pair<int, int> > coordinates; // Координаты начала и конца токена в строке.
    std::ostream& out;

    //virtual int yylex();
    int handleToken(std::string token, int& i); //Обработчик токена



public:
    MiniJavaScanner(std::istream &new_in = std::cin, std::ostream &new_out = std::cout);
    int tokenize();


    int yylex(yy::parser::semantic_type* const value=nullptr, yy::parser::location_type* location=nullptr);
};

