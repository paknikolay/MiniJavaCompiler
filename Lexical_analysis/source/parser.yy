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
%token <bool> BOOL_VALUE
%token ASSIGN_OP
%token NEGATION
%token L_BRACKET
%token R_BRACKET
%token MAIN
%token EXTENDS
%token <int> INT_VALUE
%token LENGTH
%token COMMENT


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



%left IF
%left ELSE

%left COMMA

%left ASSIGN_OP
%left BOOL_OP_OR
%left BOOL_OP_AND
%left BIN_OP_CMP
%left BIN_OP_ADD
%left BIN_OP_MULT
%right NEW
%right NEGATION

%left DOT

%right L_BRACKET
%left R_BRACKET



%right L_BRACE
%left R_BRACE
%right L_SQ_BRACKET
%left R_SQ_BRACKET
%%

program_start
    : goal { root = $1; }
goal
    : main_class class_declaration_sequence {$$ = std::make_shared<Goal>(scanner.RefreshPosition(0), $1, $2);}
    | main_class  {$$ = std::make_shared<Goal>(scanner.RefreshPosition(0), $1);}

class_declaration_sequence
    : class_declaration class_declaration_sequence {$2.push_back($1); $$ = $2;}
    | class_declaration {$$ = std::vector<std::shared_ptr<ClassDeclaration>>();  $$.push_back($1);}


main_class
    :  CLASS IDENTIFIER L_BRACE PRIVACY_MODIFIER STATIC_MODIFIER STANDARD_TYPES MAIN
       L_BRACKET STANDARD_TYPES L_SQ_BRACKET R_SQ_BRACKET IDENTIFIER R_BRACKET L_BRACE statement R_BRACE R_BRACE
         {$$ = std::make_shared<MainClass>(scanner.RefreshPosition(16), $2, $12, $15); }

class_declaration
    : class_declaration_prefix var_declaration_sequence method_declaration_sequence R_BRACE
        {$$ = std::make_shared<ClassDeclaration>(scanner.RefreshPosition(3), $1, $2, $3);}
    | class_declaration_prefix method_declaration_sequence R_BRACE
        {$$ = std::make_shared<ClassDeclaration>(scanner.RefreshPosition(2), $1, $2);}
    | class_declaration_prefix var_declaration_sequence  R_BRACE
        {$$ = std::make_shared<ClassDeclaration>(scanner.RefreshPosition(2), $1, $2);}
    | class_declaration_prefix R_BRACE
        {$$ = std::make_shared<ClassDeclaration>(scanner.RefreshPosition(1), $1);}


class_declaration_prefix
    : CLASS IDENTIFIER EXTENDS IDENTIFIER L_BRACE {scanner.RefreshPosition(4); $$ = std::make_shared<ClassDeclarationPrefix>($2, $4);}
    | CLASS IDENTIFIER L_BRACE {scanner.RefreshPosition(2);  $$ = std::make_shared<ClassDeclarationPrefix>($2);}

var_declaration
    : type IDENTIFIER SEMI_COLON {$$ = std::make_shared<VarDeclaration>(scanner.RefreshPosition(2), $1, $2);}

var_declaration_sequence
    : var_declaration {std::vector<std::shared_ptr<VarDeclaration>> array; array.push_back($1); $$ = array;}
    | var_declaration_sequence var_declaration{scanner.RefreshPosition(1); $1.push_back($2); $$ = $1;}


method_declaration
    : PRIVACY_MODIFIER type IDENTIFIER L_BRACKET R_BRACKET method_body
        {$$ = std::make_shared<MethodDeclaration>(scanner.RefreshPosition(5), $1, $2, $3, $6);}
    | PRIVACY_MODIFIER type IDENTIFIER L_BRACKET method_args method_body
        {$$ = std::make_shared<MethodDeclaration>(scanner.RefreshPosition(5), $1, $2, $3, $6, $5);}

method_declaration_sequence
    : method_declaration {std::vector<std::shared_ptr<MethodDeclaration>> array; array.push_back($1); $$ = array;}
    | method_declaration_sequence method_declaration{scanner.RefreshPosition(1); $1.push_back($2); $$ = $1;}


method_body
    : L_BRACE var_declaration_sequence statement_sequence RETURN expression SEMI_COLON R_BRACE
        {$$ = std::make_shared<MethodBody>(scanner.RefreshPosition(6), $2, $3, $5);}
    | L_BRACE statement_sequence RETURN expression SEMI_COLON R_BRACE {$$ = std::make_shared<MethodBody>(scanner.RefreshPosition(5), $2, $4);}
    | L_BRACE var_declaration_sequence RETURN expression SEMI_COLON R_BRACE {$$ = std::make_shared<MethodBody>(scanner.RefreshPosition(5), $2, $4);}
    | L_BRACE RETURN expression SEMI_COLON R_BRACE {$$ = std::make_shared<MethodBody>(scanner.RefreshPosition(4), $3);}

method_args
    : type IDENTIFIER COMMA method_args {scanner.RefreshPosition(3); $4.push_back(std::make_pair($1, $2)); $$ = $4;}
    | type IDENTIFIER R_BRACKET {scanner.RefreshPosition(2); $$ = std::vector<std::pair<std::shared_ptr<Type>, std::string>>(); $$.push_back(std::make_pair($1,$2));}


type
    : STANDARD_TYPES {$$ = std::make_shared<Type>(scanner.RefreshPosition(0), Type::EType::STANDARD_TYPE, $1);}
    | STANDARD_TYPES L_SQ_BRACKET R_SQ_BRACKET {$$ = std::make_shared<Type>(scanner.RefreshPosition(2), Type::EType::STANDARD_TYPE_ARRAY, $1);}
    | IDENTIFIER {$$ = std::make_shared<Type>(scanner.RefreshPosition(0), Type::EType::IDENTIFIER, $1);}

statement
    : L_BRACE statement_sequence R_BRACE {$$ = std::make_shared<StatementSequence>(scanner.RefreshPosition(2), $2);}
    | L_BRACE R_BRACE {$$ = std::make_shared<StatementBase>(scanner.RefreshPosition(1));}
    | IF L_BRACKET expression R_BRACKET statement ELSE statement {$$ = std::make_shared<StatementIf>(scanner.RefreshPosition(6), $3, $5, $7);}
    | WHILE L_BRACKET expression R_BRACKET statement {$$ = std::make_shared<StatementWhile>(scanner.RefreshPosition(4), $3, $5);}
    | OUT L_BRACKET expression R_BRACKET SEMI_COLON {$$ = std::make_shared<StatementPrint>(scanner.RefreshPosition(4), $3);}
    | IDENTIFIER ASSIGN_OP expression SEMI_COLON {$$ = std::make_shared<StatementAssign>(scanner.RefreshPosition(3), $1, $3);}
    | IDENTIFIER L_SQ_BRACKET expression R_SQ_BRACKET ASSIGN_OP expression SEMI_COLON {$$ = std::make_shared<StatementAssignContainerElement>(scanner.RefreshPosition(6), $1, $3, $6);}

statement_sequence
    : statement {std::vector<std::shared_ptr<StatementBase>> array; array.push_back($1); $$ = array; }
    | statement_sequence statement{scanner.RefreshPosition(1), $1.push_back($2); $$ = $1;}


expression
    : expression BIN_OP_ADD expression {$$ = std::make_shared<ExpressionBinOp>(scanner.RefreshPosition(2), $1, $3, $2); }
    | expression BIN_OP_MULT expression {$$ = std::make_shared<ExpressionBinOp>(scanner.RefreshPosition(2), $1, $3, $2);}
    | expression BIN_OP_CMP expression {$$ = std::make_shared<ExpressionBinOp>(scanner.RefreshPosition(2), $1, $3, $2);}
    | expression BOOL_OP_AND expression {$$ = std::make_shared<ExpressionBinOp>(scanner.RefreshPosition(2), $1, $3, $2);}
    | expression BOOL_OP_OR expression {$$ = std::make_shared<ExpressionBinOp>(scanner.RefreshPosition(2), $1, $3, $2);}

    | THIS {$$ = std::make_shared<ExpressionThis>(scanner.RefreshPosition(0));}

    | expression L_SQ_BRACKET expression R_SQ_BRACKET {$$ = std::make_shared<ExpressionIndex>(scanner.RefreshPosition(3), $1, $3);}

    | expression DOT LENGTH {$$ = std::make_shared<ExpressionGetLength>(scanner.RefreshPosition(2), $1);}

    | expression DOT IDENTIFIER L_BRACKET R_BRACKET {$$ = std::make_shared<ExpressionFunctionCall>(scanner.RefreshPosition(4), $1, $3);}

    | expression DOT IDENTIFIER L_BRACKET few_expressions R_BRACKET {$$ = std::make_shared<ExpressionFunctionCall>(scanner.RefreshPosition(5), $1, $3, $5);}

    | INT_VALUE {$$ = std::make_shared<ExpressionInt>(scanner.RefreshPosition(0), $1); }
    | BOOL_VALUE {$$ = std::make_shared<ExpressionBool>(scanner.RefreshPosition(0), $1); }
    | NEW STANDARD_TYPES L_SQ_BRACKET expression R_SQ_BRACKET {$$ = std::make_shared<ExpressionNewIntArray>(scanner.RefreshPosition(4), $4);}
    | NEGATION expression {$$ = std::make_shared<ExpressionNegation>(scanner.RefreshPosition(1), $2);}
    | IDENTIFIER {$$ = std::make_shared<ExpressionIdentifier>(scanner.RefreshPosition(0), $1); }
    | NEW IDENTIFIER L_BRACKET R_BRACKET {$$ = std::make_shared<ExpressionNewIdentifier>(scanner.RefreshPosition(3), $2);}
    | L_BRACKET expression R_BRACKET {scanner.RefreshPosition(2); $$ = $2;}

few_expressions
    : few_expressions COMMA expression {scanner.RefreshPosition(2); $1.push_back($3); $$ = $1;}
    | expression {std::vector<std::shared_ptr<ExpressionBase>> array; array.push_back($1); $$ = array;}

%%

void yy::parser::error (const location_type& l, const std::string& m) {
    std::cerr << m << " at " << l << " (in raw " << scanner.getCurrentRaw() << ")" << std::endl;
}