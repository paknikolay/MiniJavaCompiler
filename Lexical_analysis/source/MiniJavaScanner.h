#pragma once

#include <vector>
#include <string>

#if !defined (yyFlexLexerOnce)
#include <FlexLexer.h>
#endif // _!defined (yyFlexLexerOnce)

#include "parser.hh"
#include "Enums.h"

using Token = yy::parser::token::yytokentype;

class MiniJavaScanner : public yyFlexLexer {
public:
    std::vector<std::pair<int, int>> positions;
    std::pair<int, int> RefreshPosition(int tailLength, bool debug_mode = false) {
        if (debug_mode) {
            for (int i = 0; i < positions.size(); ++i) {
                std::cout << "{" << positions[i].first << "," << positions[i].second << "}";
            }
            std::cout << std::endl;
        }

        for (int i = 0; i < tailLength; ++i) {
            positions.pop_back();
        }
        return positions[positions.size() - 1];
    }
    void printPositionsVector(){
        std::cout << "_________________\n";
        for (auto pair : positions) {
            std::cout<<pair.first << " " << pair.second <<"\n";
        }
        std::cout << "_________________\n";
    }

private:
    std::vector< std::pair<int, int> > coordinates; // Координаты начала и конца токена в строке.
    int currentRaw = 1;
    int positionInRaw = 1;
    std::ostream& out;


    void updateRaw();
    //virtual int yylex();
    Token handleToken(Token token, int& i); //Обработчик токена

    yy::parser::semantic_type* yylval = nullptr;
    yy::parser::location_type* loc = nullptr;

    template<typename T>
    void Build(const T& value) {
       /* if (yylval == nullptr) {
            return;
        }*/
        yylval->build<T>(value);

        //out << "\n" << value << " - value of handled token\n";
    }

 /*   void Build(const EModifier& value) {
        out << ((int) value) << " - value of handled token\n";
    }
    void Build(const EBool& value) {
        out << ((int) value) << " - value of handled token";
    }
    void Build(const EBinOp& value) {
        out << ((int) value) << " - value of handled token";
    }
*/
public:
    MiniJavaScanner(std::istream &new_in = std::cin, std::ostream &new_out = std::cout);
    int tokenize();


    int yylex(yy::parser::semantic_type* const value=nullptr, yy::parser::location_type* location=nullptr);
    int getCurrentRaw() const {
        return currentRaw;
    }
};

