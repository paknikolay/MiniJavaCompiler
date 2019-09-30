%{
    #include <iostream>
    #include "MiniJavaScanner.h"
%}

%option noyywrap
%option c++
%option yyclass="MiniJavaScanner"

SPACE    [ \t\n]+
DIGIT    [0-9]
LETTER   [a-z|A-Z]
ID       ({LETTER}|_)({LETTER}|{DIGIT}|_)*
INTEGER  [1-9]{DIGIT}*|0
REAL     {DIGIT}*"."{DIGIT}+|{DIGIT}+"."{DIGIT}*

%%

%{
    int i = 0;
%}


{SPACE}    { i += yyleng; }

"class"    { handleToken("CLASS", i); }

"if"    { handleToken("IF", i); }

"else"    { handleToken("ELSE", i); }

"while"    { handleToken("WHILE", i); }

"return"    { handleToken("RETURN", i); }

"new"    { handleToken("OP_NEW", i); }

"this"    { handleToken("THIS", i); }

"System.out.println"    { handleToken("OUT", i); }

"int"|"boolean"|"String"|"void"|"List"    { handleToken("TYPE", i); }

"public"|"private"|"static"    { handleToken("MODIFIER", i); }

"true"|"false"    { handleToken("BOOL_VALUE", i); }

{ID}    { handleToken("ID", i); } 

"."{ID}    { handleToken("METHOD", i); }

"\""[^"\""]*"\""    { handleToken("STRING", i); }

"'"[^"'"]"'"    { handleToken("CHAR", i); }
 
{INTEGER}   { handleToken("INT", i); }

{REAL}   { handleToken("REAL", i); }

";"    { handleToken("SEMICOLON", i); }

","    { handleToken("COMMA", i); }

"="    { handleToken("ASSIGN_OP", i); }

"&&"|"||"   { handleToken("BOOL_OP", i); }

"//"[^\n]*  { handleToken("COMMENT", i); }

"+"|"-"|"*"|"/"   { handleToken("OP", i); }

"<"|">"|"=="|"<="|">="|"!="   { handleToken("COMP_OP", i); }

"!"    { handleToken("NOT", i); }

"{"    { handleToken("L_BRACE", i); }

"}"    { handleToken("R_BRACE", i); }

"("    { handleToken("L_BRACKET", i); }

")"    { handleToken("R_BRACKET", i); }

"["    { handleToken("L_SQ_BRACKET", i); }

"]"    { handleToken("R_SQ_BRACKET", i); }

.     { std::cout << std::endl << "Unrecognized character: " << yytext << std::endl; }

%%


