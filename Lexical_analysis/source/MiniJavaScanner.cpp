#include <iostream>
#include <cstring>
#include <parser.hh>
#include "MiniJavaScanner.h"
#include "Enums.h"

bool StringsEqual(const char* first, const char* second) {
    return strcmp(first, second) == 0;
}

int MiniJavaScanner::handleToken(Token token, int& i)
{
    std::pair<int, int> token_coords;
    token_coords.first = i + 1;
    out << token << ' ';
    i += yyleng;
    token_coords.second = i;
    coordinates.push_back(token_coords);

    switch (token) {
        case Token::REAL_VALUE: {
            Build(std::stof(YYText()));
            break;
        }
        case Token::PRIVACY_MODIFIER: {
            Build(StringsEqual(YYText(), "private") ? EModifier::PRIVATE : EModifier::PUBLIC);
            break;
        }
        case Token::BIN_OP_MULT: {
            Build(EBinOp::MUL);
            break;
        }
        case Token::BIN_OP_ADD: {
            Build(EBinOp::PLUS);
            break;
        }
        case Token::BIN_OP_CMP: {
            if (StringsEqual(YYText(), "!=")) {
                Build(EBinOp::NEQ);
            }
            if (StringsEqual(YYText(), "==")) {
                Build(EBinOp::EQ);
            }
            if (StringsEqual(YYText(), "<=")) {
                Build(EBinOp::LE);
            }
            if (StringsEqual(YYText(), ">=")) {
                Build(EBinOp::GE);
            }
            if (StringsEqual(YYText(), "<")) {
                Build(EBinOp::L);
            }
            if (StringsEqual(YYText(), ">")) {
                Build(EBinOp::G);
            }
            break;
        }
        case Token::BOOL_VALUE: {
            Build(StringsEqual(YYText(), "false") ? EBool::FALSE : EBool::TRUE);
            break;
        }
        case Token::INT_VALUE: {
            Build(std::stoll(YYText()));
        }

    }


    //return Token::THIS;
}

int MiniJavaScanner::tokenize()
{
    yylex();
    std::cout << std::endl << "Coordinates of tokens:" << std::endl;
    std::cout << "| ";
    for (std::pair<int, int> token: coordinates) {
        std::cout << token.first << ' ' << token.second << " | ";
    }
    std::cout << std::endl;
    return 0;
}

MiniJavaScanner::MiniJavaScanner(std::istream &new_in, std::ostream &new_out) : out(new_out) {
    yyFlexLexer::switch_streams(new_in, std::cout);
}

