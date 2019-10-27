%require "3.2"
%language "c++"

%define api.value.type variant

%locations

%code requires{
    #include <vector>
    #include <string>
    #include "Enums.h"
    #include "Expression/Expressions.h"
    #include "Statement/Statements.h"
    #include "Goal/Goal.h"
    #include "MainClass/MainClass.h"
    #include "MethodDeclaration/MethodDeclaration.h"
    #include "VarDeclaration/VarDeclaration.h"
    #include "Type/Type.h"
    class MiniJavaScanner;
}

%parse-param { MiniJavaScanner& scanner }
%parse-param { std::shared_ptr<BaseNode>& root }

%code {
    #include "MiniJavaScanner.h"
    #include <memory>

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
%token <EBinOp> BOOL_OP_AND
%token <EBinOp> BOOL_OP_OR
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
%token <std::string> STANDARD_TYPES
%token <EBool> BOOL_VALUE
%token ASSIGN_OP
%token NEGATION
%token L_BRACKET
%token R_BRACKET
%token MAIN
%token EXTENDS
%token <int> INT_VALUE
%token LENGTH


%type program_start

%token <std::string> IDENTIFIER

%type <std::shared_ptr<Goal>> goal
%type <std::shared_ptr<MainClass>> main_class

%type <std::shared_ptr<ClassDeclarationPrefix>> class_declaration_prefix
%type <std::shared_ptr<ClassDeclaration>> class_declaration
%type <std::vector<std::shared_ptr<ClassDeclaration>>> class_declaration_sequence

%type <std::shared_ptr<Type>> type

%type <std::shared_ptr<VarDeclaration>> var_declaration
%type <std::vector<std::shared_ptr<VarDeclaration>>> var_declaration_sequence

%type <std::shared_ptr<MethodDeclaration>> method_declaration
%type <std::vector<std::pair<std::shared_ptr<Type>, std::string>>> method_args
%type <std::shared_ptr<MethodBody>> method_body
%type <std::vector<std::shared_ptr<MethodDeclaration>>> method_declaration_sequence

%type <std::shared_ptr<StatementBase>> statement
%type <std::vector<std::shared_ptr<StatementBase>>> statement_sequence

%type <std::shared_ptr<ExpressionBase>> expression
%type <std::vector<std::shared_ptr<ExpressionBase>>> few_expressions


%%
program_start
    : goal { root = $1; }
goal
    : main_class class_declaration_sequence EOF_TOKEN {$$ = std::make_shared<Goal>($1, $2);}
    | main_class EOF_TOKEN  {$$ = std::make_shared<Goal>($1);}

class_declaration_sequence
    : class_declaration class_declaration_sequence {$2.push_back($1); $$ = $2;}
    | class_declaration {$$ = std::vector<std::shared_ptr<ClassDeclaration>>();  $$.push_back($1);}


main_class
    :  CLASS IDENTIFIER L_BRACKET PRIVACY_MODIFIER STATIC_MODIFIER STANDARD_TYPES MAIN
       R_BRACKET STANDARD_TYPES IDENTIFIER R_BRACKET L_BRACE statement R_BRACE R_BRACE
         {$$ = std::make_shared<MainClass>($2, $10, $13);}


class_declaration
    : class_declaration_prefix L_BRACE var_declaration_sequence method_declaration_sequence R_BRACE
        {$$ = std::make_shared<ClassDeclaration>($1, $3, $4);}
    | class_declaration_prefix L_BRACE method_declaration_sequence R_BRACE
        {$$ = std::make_shared<ClassDeclaration>($1, $3);}
    | class_declaration_prefix L_BRACE var_declaration_sequence  R_BRACE
        {$$ = std::make_shared<ClassDeclaration>($1, $3);}
    | class_declaration_prefix L_BRACE R_BRACE
        {$$ = std::make_shared<ClassDeclaration>($1);}


class_declaration_prefix
    : CLASS IDENTIFIER EXTENDS IDENTIFIER {$$ = std::make_shared<ClassDeclarationPrefix>($2, $4);}
    | CLASS IDENTIFIER {$$ = std::make_shared<ClassDeclarationPrefix>($2);}


var_declaration
    : type IDENTIFIER SEMI_COLON {$$ = std::make_shared<VarDeclaration>($1, $2);}

var_declaration_sequence
    : var_declaration {std::vector<std::shared_ptr<VarDeclaration>> array; array.push_back($1); $$ = array;}
    | var_declaration var_declaration_sequence {$2.push_back($1); $$ = $2;}

method_declaration
    : PRIVACY_MODIFIER type IDENTIFIER L_BRACKET R_BRACKET method_body
        {$$ = std::make_shared<MethodDeclaration>($1, $2, $3, $6);}
    | PRIVACY_MODIFIER type IDENTIFIER L_BRACKET method_args R_BRACKET method_body
        {$$ = std::make_shared<MethodDeclaration>($1, $2, $3, $7, $5);}

method_declaration_sequence
    : method_declaration {std::vector<std::shared_ptr<MethodDeclaration>> array; array.push_back($1); $$ = array;}
    | method_declaration method_declaration_sequence {$2.push_back($1); $$ = $2;}


method_body
    : L_BRACE var_declaration_sequence statement_sequence RETURN expression SEMI_COLON R_BRACE
        {$$ = std::make_shared<MethodBody>($2, $3, $5);}
    | L_BRACE statement_sequence RETURN expression SEMI_COLON R_BRACE {$$ = std::make_shared<MethodBody>($2, $4);}
    | L_BRACE var_declaration_sequence RETURN expression SEMI_COLON R_BRACE {$$ = std::make_shared<MethodBody>($2, $4);}
    | L_BRACE RETURN expression SEMI_COLON R_BRACE {$$ = std::make_shared<MethodBody>($3);}

method_args
    : type IDENTIFIER COMMA method_args {$4.push_back(std::make_pair($1, $2)); $$ = $4;}
    | type IDENTIFIER {$$ = std::vector<std::pair<std::shared_ptr<Type>, std::string>>();}

type
    : STANDARD_TYPES {$$ = std::make_shared<Type>(Type::EType::STANDARD_TYPE, $1);}
    | STANDARD_TYPES L_SQ_BRACKET R_SQ_BRACKET {$$ = std::make_shared<Type>(Type::EType::STANDARD_TYPE_ARRAY, $1);}
    | IDENTIFIER {$$ = std::make_shared<Type>(Type::EType::IDENTIFIER, $1);}

statement
    : L_BRACE statement_sequence R_BRACE {$$ = std::make_shared<StatementSequence>($2);}
    | L_BRACE R_BRACE {$$ = std::make_shared<StatementBase>();}
    | IF L_BRACKET expression R_BRACKET statement ELSE statement {$$ = std::make_shared<StatementIf>($3, $5, $7);}
    | WHILE L_BRACKET expression R_BRACKET statement {$$ = std::make_shared<StatementWhile>($3, $5);}
    | OUT L_BRACKET expression R_BRACKET SEMI_COLON {$$ = std::make_shared<StatementPrint>($3);}
    | IDENTIFIER ASSIGN_OP expression SEMI_COLON {$$ = std::make_shared<StatementAssign>($1, $3);}
    | IDENTIFIER L_SQ_BRACKET expression R_SQ_BRACKET ASSIGN_OP expression SEMI_COLON {$$ = std::make_shared<StatementAssignContainerElement>($1, $3, $6);}

statement_sequence
    : statement {std::vector<std::shared_ptr<StatementBase>> array; array.push_back($1); $$ = array;}
    | statement statement_sequence {$2.push_back($1); $$ = $2;}


expression
    : expression BIN_OP_ADD expression {$$ = std::make_shared<ExpressionBinOp>($1, $3, $2);}
    | expression BIN_OP_MULT expression {$$ = std::make_shared<ExpressionBinOp>($1, $3, $2);}
    | expression BIN_OP_CMP expression {$$ = std::make_shared<ExpressionBinOp>($1, $3, $2);}
    | expression BOOL_OP_AND expression {$$ = std::make_shared<ExpressionBinOp>($1, $3, $2);}
    | expression BOOL_OP_OR expression {$$ = std::make_shared<ExpressionBinOp>($1, $3, $2);}
    | THIS {$$ = std::make_shared<ExpressionThis>();}
    | expression L_SQ_BRACKET expression R_SQ_BRACKET {$$ = std::make_shared<ExpressionIndex>($1, $3);}
    | expression DOT LENGTH {$$ = std::make_shared<ExpressionGetLength>($1);}
    | expression DOT IDENTIFIER L_BRACKET R_BRACKET {$$ = std::make_shared<ExpressionFunctionCall>($1, $3);}
    | expression DOT IDENTIFIER L_BRACKET few_expressions R_BRACKET {$$ = std::make_shared<ExpressionFunctionCall>($1, $3, $5);}
    | INT_VALUE {$$ = std::make_shared<ExpressionInt>($1);}
    | NEW STANDARD_TYPES R_SQ_BRACKET expression L_SQ_BRACKET {$$ = std::make_shared<ExpressionNewIntArray>($4);}
    | NEGATION expression {$$ = std::make_shared<ExpressionNegation>($2);}
    | IDENTIFIER {$$ = std::make_shared<ExpressionIdentifier>($1); }
    | NEW IDENTIFIER L_BRACKET R_BRACKET {$$ = std::make_shared<ExpressionNewIdentifier>($2);}
    | NEGATION L_BRACKET expression R_BRACKET {$$ = std::make_shared<ExpressionNegation>($3);}

few_expressions
    : expression COLON few_expressions {$3.push_back($1); $$ = $3;}
    | expression {std::vector<std::shared_ptr<ExpressionBase>> array; array.push_back($1); $$ = array;}

%%

void yy::parser::error (const location_type& l, const std::string& m) {
    std::cerr << m << " at " << l << std::endl;
}