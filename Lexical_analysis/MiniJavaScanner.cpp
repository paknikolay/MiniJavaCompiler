#include <iostream>
#include <string>

#include "MiniJavaScanner.h"

int MiniJavaScanner::handleToken(std::string token, int& i)
{
    std::pair<int, int> token_coords;
    token_coords.first = i + 1;
    std::cout << token << ' ';
    i += yyleng;
    token_coords.second = i;
    coordinates.push_back(token_coords);
    return 0;
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
