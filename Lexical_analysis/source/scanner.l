%{
    #include <iostream>
    #include "MiniJavaScanner.h"
    #undef YY_DECL
    #define YY_DECL int MiniJavaScanner::yylex(yy::parser::semantic_type* const value, yy::parser::location_type* location)


%}

%option noyywrap nounput noinput
%option c++
%option yyclass="MiniJavaScanner"


SPACE       [ \t\n]+
DIGIT       [0-9]
LETTER      [a-zA-Z]
ID          ({LETTER}|_)({LETTER}|{DIGIT}|_)*
INTEGER_VALUE     [1-9]{DIGIT}*|0
REAL_VALUE        {DIGIT}*"."{DIGIT}+|{DIGIT}+"."{DIGIT}*
BIN_OP_MULT [*/%]
BIN_OP_ADD  [+\-]
BIN_OP_CMP  <|>|"=="|"<="|">="|"!="
BOOL_OP_AND "&&"
BOOL_OP_OR  "||"
DOT         "."
COLON       ":"
MAIN        ""
EXTENDS     "extends"
LENGTH      "length"
THIS        "this"

%%

%{
    int i = 0;

    yylval = value;
    loc = location;
%}

EXTENDS {return handleToken(Token::EXTENDS, i);}
"main" {return handleToken(Token::MAIN, i);}
"class"    { return handleToken(Token::CLASS, i); }

"if"    { return handleToken(Token::IF, i); }

"else"    { return handleToken(Token::ELSE, i); }

"while"    { return handleToken(Token::WHILE, i); }

"return"    { return handleToken(Token::RETURN, i); }

"new"    { return handleToken(Token::NEW, i); }

"System.out.println"    { return handleToken(Token::OUT, i); }
"int"|"boolean"|"String"|"void"|"List"    { return handleToken(Token::STANDARD_TYPES, i); }

"public"|"private"    { return handleToken(Token::PRIVACY_MODIFIER, i); }
"static"            { return handleToken(Token::STATIC_MODIFIER, i); }
{LENGTH}           { return handleToken(Token::LENGTH, i); }
{THIS}           { return handleToken(Token::THIS, i); }

"true"|"false"    { return handleToken(Token::BOOL_VALUE, i); }

{ID}    { return handleToken(Token::IDENTIFIER, i); }

{DOT}    { return handleToken(Token::DOT, i); }

{INTEGER_VALUE}   { return handleToken(Token::INT_VALUE, i); }

{REAL_VALUE}   { return handleToken(Token::REAL_VALUE, i); }

";"    { return handleToken(Token::SEMI_COLON, i); }

","    { return handleToken(Token::COMMA, i); }

"="    { return handleToken(Token::ASSIGN_OP, i); }

{BOOL_OP_AND}   { return handleToken(Token::BOOL_OP_AND, i); }
{BOOL_OP_OR}   { return handleToken(Token::BOOL_OP_OR, i); }

"//"[^\n]*  { /*return handleToken(Token::COMMENT, i);*/ }

{BIN_OP_MULT}    { return handleToken(Token::BIN_OP_MULT, i);  }
{BIN_OP_ADD}    { return handleToken(Token::BIN_OP_ADD, i); }
{BIN_OP_CMP}    { return handleToken(Token::BIN_OP_CMP, i); }

"!"    { return handleToken(Token::NEGATION, i); }

"{"    { return handleToken(Token::L_BRACE, i); }

"}"    { return handleToken(Token::R_BRACE, i); }

"("    { return handleToken(Token::L_BRACKET, i); }

")"    { return handleToken(Token::R_BRACKET, i); }

"["    { return handleToken(Token::L_SQ_BRACKET, i); }

"]"    { return handleToken(Token::R_SQ_BRACKET, i); }
{COLON}    { return handleToken(Token::COLON, i); }

<<EOF>> {return 0; }

{SPACE}    { i += yyleng; }
.     { std::cout << std::endl << "Unrecognized character: " << yytext << std::endl; }

%%


