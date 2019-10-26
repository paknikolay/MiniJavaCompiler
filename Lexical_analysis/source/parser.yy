%require "3.2"
%language "c++"

%define api.value.type variant

%locations

%code requires{
    #include "Enums.h"

    class MiniJavaScanner;
}

%parse-param { MiniJavaScanner& scanner }
//%parse-param { TreeNodePtr& result }

%code {
    #include "MiniJavaScanner.h"

#undef yylex
#define yylex scanner.yylex
/*
Position toPos(const yy::location& from, const yy::location& to) {
    return Position{
        static_cast<int>(from.begin.line), static_cast<int>(to.end.line),
        static_cast<int>(from.begin.column), static_cast<int>(to.end.column)
    };
}
*/

}

%token EOF_TOKEN


%token <std::string> INDENTIFIER

%token SPACE
%token DIGIT
%token LETTER
%token <double> REAL_VALUE
%token BOOL_OP_AND
%token BOOL_OP_OR
%token COLON
%token SEMI_COLON
%token CLASS
%token <EModifier>PRIVACY_MODIFIER
%token STATIC_MODIFIER
%token DOT
%token L_BRACE
%token R_BRACE
%token L_SQ_BRACKET
%token R_SQ_BRACKET
%token COMMA
%token <EBinOp> BIN_OP_MULT
%token <EBinOp> BIN_OP_ADD
%token <EBinOp> BIN_OP_CMP
%token IF
%token ELSE
%token WHILE
%token RETURN
%token NEW
%token THIS
%token OUT
%token STANDARD_TYPES
%token <EBool> BOOL_VALUE
%token ASSIGN_OP
%token NEGATION
%token L_BRACKET
%token R_BRACKET
%token MAIN
%token EXTENDS
%token <int> INT_VALUE
%token LENGTH


%token <std::string> IDENTIFIER

/*
to do please to lower
%
type GOAL
%type MAIN_CLASS
%type CLASS_DECLARATION
%type TYPE
%type VAR_DECLARATION
%type METHOD_DECLARATION
%type STATEMENT
*/
%type expression

/*
//////////////////////////////////////////

%type <std::string> id
%type arg
%type type_decl
%type <TreeNodePtr> method_signature
%type <TreeNodePtr> method
%type <TreeNodePtr> method_list
%type program
%type <TreeNodePtr> exp
%type <TreeNodePtr> exp_list

%left NL
%left IF
%left ELSE
%left BIN_OP_CMP
%left BIN_OP_ADD
%left BIN_OP_MULT
%left DOT
%left L_SQ_BRACE
////////////////////////////////////////////////////
*/

%%
/*
goal
    : main_class classes_declaration

classes_declaration
    : class_declaration classes_declaration
    | EOF_TOKEN

main_class
    :  CLASS IDENTIFIER L_BRACKET PRIVACY_MODIFIER STATIC_MODIFIER STANDARD_TYPE MAIN
       R_BRACKET STANDARD_TYPE IDENTIFIER R_BRACKET L_BRACE statement R_BRACE R_BRACE

class_declaration
    : class_declaration_prefix L_BRACE class_declaration_body

class_declaration_prefix
    : CLASS IDENTIFIER L_BRACKET EXTENDS IDENTIFIER R_BRACKET
    | CLASS IDENTIFIER

class_declaration_body
    : var_declaration class_declaration_body
    | class_declaration_postfix

class_declaration_postfix
    : method_declaration class_declaration_postfix
    | R_BRACE

var_declaration
    : STANDARD_TYPE IDENTIFIER SEMI_COLON

var_declaration_sequence
    : var_declaration
    | var_declaration var_declaration_sequence
    
method_declaration
    : PRIVACY_MODIFIER STANDARD_TYPE IDENTIFIER L_BRACKET R_BRACKET method_body
    | PRIVACY_MODIFIER STANDARD_TYPE IDENTIFIER L_BRACKET method_args R_BRACKET method_body

method_body
    : L_BRACE var_declaration_sequence statement_sequence RETURN expression SEMICOLON R_BRACE
    | L_BRACE statement_sequence RETURN expression SEMICOLON R_BRACE
    | L_BRACE var_declaration_sequence RETURN expression SEMICOLON R_BRACE
    | L_BRACE RETURN expression SEMICOLON R_BRACE

method_args
    : STANDARD_TYPE IDENTIFIER COMMA method_args
    | STANDARD_TYPE IDENTIFIER

type
    : STANDARD_TYPE
    | STANDARD_TYPE L_SQ_BRACKET R_SQ_BRACKET
    | IDENTIFIER

statement
    : L_BRACE statement_sequence R_BRACE
    | L_BRACE R_BRACE
    | IF L_BRACKET expression R_BRACKET statement ELSE statement
    | WHILE L_BRACKET expression R_BRACKET statement
    | OUT L_BRACKET expression R_BRACKET SEMICOLON
    | IDENTIFIER ASSIGN_OP expression SEMICOLON
    | IDENTIFIER L_SQ_BRACKET expression R_SQ_BRACKET ASSIGN_OP expression SEMICOLON

statement_sequence
    : statement
    | statement statement_sequence

*/

/*
expression
    : expression BIN_OP_ADD expression {ExpressionBinOp}
    | expression BIN_OP_MULT expression {ExpressionBinOp}
    | expression BIN_OP_CMP expression {ExpressionBinOp}
    | expression BOOL_OP_AND expression {ExpressionBinOp}
    | expression BOOL_OP_OR expression {ExpressionBinOp}
    | expression L_SQ_BRACKET expression R_SQ_BRACKET {ExpressionIndex}
    | expression DOT LENGTH {ExpressinGetLength}
    | expression DOT IDENTIFIER L_BRACKET R_BRACKET {ExpressionFunctionCall}
    | expression DOT IDENTIFIER L_BRACKET few_expressions R_BRACKET {ExpressionFunctionCall}
    | INT_VALUE {ExpressionInt}
    | THIS {ExpressionThis}
    | NEW STANDARD_TYPES R_SQ_BRACKET expression L_SQ_BRACKET {ExpressionNewIntArray}
    | NEW IDENTIFIER L_BRACKET R_BRACKET {ExpressionNewIdentifier}
    | NEGATION expression {ExpressionNegation}
    | NEGATION L_BRACKET expression R_BRACKET {ExpressionNegation}

few_expressions
    : expression COLON few_expressions {}
    | expression {}


*/
integer
    : NEGATION {}

/*
program
    : method_list END       { result = $1; }
    | method_list NL END    { result = $1; }

arg
    : id type_decl    {  }

type_decl
    : INT       { }
    | LIST      { }

method_signature
    : DEF id                                 { $$ = MakeSeq({ MakeValue("def"), MakeValue($2) }); }
    | DEF id L_BRACE arg R_BRACE             { $$ = MakeSeq({ MakeValue("def"), MakeValue($2) }); }

method
    : method_signature COLON NL exp           { $$ = MakeSeq({ $1, MakeValue(":"), $4 }); }
    | method_signature type_decl COLON NL exp { $$ = MakeSeq({ $1, MakeValue(":"), $5 }); }

method_list
    : method                    { $$ = $1; }
    | method_list method        { $$ = MakeSeq({ $1, $2 }); }

id
    : NAME   { $$ = $1; }

exp_list
    : exp COMMA exp         { $$ = MakeSeq({ $1, MakeValue(","), $3 }); }
    | exp_list COMMA exp    { $$ = MakeSeq({ $1, MakeValue(","), $3 });}

exp
    : L_SQ_BRACE exp_list R_SQ_BRACE        { $$ = MakeSeq({ MakeValue("["), $2, MakeValue("]") }); }
    | L_SQ_BRACE exp R_SQ_BRACE             { $$ = MakeSeq({ MakeValue("["), $2, MakeValue("]") }); }
    | L_SQ_BRACE R_SQ_BRACE                 { $$ = MakeSeq({ MakeValue("["), MakeValue("]") }); }
    | exp IF exp ELSE exp                   { $$ = MakeSeq({ $1, MakeValue("if"), $3, MakeValue("else"), $5 });  }
    | exp BIN_OP_MULT exp                   { $$ = MakeSeq({ $1, MakeValue($2), $3 }); }
    | exp BIN_OP_ADD exp                    { $$ = MakeSeq({ $1, MakeValue($2), $3 }); }
    | exp BIN_OP_CMP exp                    { $$ = MakeSeq({ $1, MakeValue($2), $3 }); }
    | exp DOT id L_BRACE exp_list R_BRACE   { $$ = MakeSeq({ $1, MakeValue("."), MakeValue($3), MakeValue("("), $5, MakeValue(")") }); }
    | exp DOT id                            { $$ = MakeSeq({ $1, MakeValue("."), MakeValue($3)}); }
    | exp DOT id L_BRACE exp R_BRACE        { $$ = MakeSeq({ $1, MakeValue("."), MakeValue($3), MakeValue("("), $5, MakeValue(")") }); }
    | id                                    { $$ = MakeValue($1); }
    | INT_CONST                             { $$ = MakeValue(std::to_string($1)); }
    | exp L_SQ_BRACE exp R_SQ_BRACE         { $$ = MakeSeq({ $1, MakeValue("["), $3, MakeValue("]") }); }
    | exp L_SQ_BRACE exp COLON R_SQ_BRACE   { $$ = MakeSeq({ $1, MakeValue("["), $3, MakeValue(":"), MakeValue("]") }); }
    | L_BRACE exp R_BRACE                   { $$ = MakeSeq({ MakeValue("("), $2, MakeValue(")") }); }
*/
%%

void yy::parser::error (const location_type& l, const std::string& m) {
    std::cerr << m << " at " << l << std::endl;
}