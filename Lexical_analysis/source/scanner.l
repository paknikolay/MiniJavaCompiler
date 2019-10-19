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
%}

EXTENDS {return handleToken("EXTENDS", i);}
"main" {return handleToken("main", i);}
"class"    { return handleToken("CLASS", i); }

"if"    { return handleToken("IF", i); }

"else"    { return handleToken("ELSE", i); }

"while"    { return handleToken("WHILE", i); }

"return"    { return handleToken("RETURN", i); }

"new"    { return handleToken("NEW", i); }

"System.out.println"    { return handleToken("OUT", i); }
"int"|"boolean"|"String"|"void"|"List"    { return handleToken("STANDARD_TYPES", i); }

"public"|"private"    { return handleToken("PRIVACY_MODIFIER", i); }
"static"            { return handleToken("STATIC", i); }
{LENGTH}           { return handleToken("LENGTH", i); }
{THIS}           { return handleToken("THIS", i); }

"true"|"false"    { return handleToken("BOOL_VALUE", i); }

{ID}    { return handleToken("INDENTIFIER", i); }

{DOT}    { return handleToken("DOT", i); }

{INTEGER_VALUE}   { return handleToken("INT_VALUE", i); }

{REAL_VALUE}   { return handleToken("REAL_VALUE", i); }

";"    { return handleToken("SEMICOLON", i); }

","    { return handleToken("COMMA", i); }

"="    { return handleToken("ASSIGN_OP", i); }

{BOOL_OP_AND}   { return handleToken("BOOL_OP_AND", i); }
{BOOL_OP_OR}   { return handleToken("BOOL_OP_OR", i); }

"//"[^\n]*  { return handleToken("COMMENT", i); }

{BIN_OP_MULT}    { return handleToken("BIN_OP_MULT", i);  }
{BIN_OP_ADD}    { return handleToken("BIN_OP_ADD", i); }
{BIN_OP_CMP}    { return handleToken("BIN_OP_CMP", i); }


{BIN_OP_CMP}  { return handleToken("COMP_OP", i); }

"!"    { return handleToken("NEGATION", i); }

"{"    { return handleToken("L_BRACE", i); }

"}"    { return handleToken("R_BRACE", i); }

"("    { return handleToken("L_BRACKET", i); }

")"    { return handleToken("R_BRACKET", i); }

"["    { return handleToken("L_SQ_BRACKET", i); }

"]"    { return handleToken("R_SQ_BRACKET", i); }
{COLON}    { return handleToken("COLON", i); }

{SPACE}    { i += yyleng; }
.     { std::cout << std::endl << "Unrecognized character: " << yytext << std::endl; }

%%


