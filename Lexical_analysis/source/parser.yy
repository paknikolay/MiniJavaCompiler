%require "3.2"
%language "c++"

%define api.value.type variant

%locations

%code requires{
    #include <vector>
    #include <string>
    #include "Enums.h"
    #include "Expression/Expressions.h"
//    #include "Statement/Statements.h"
    #include "Type/Type.h"
    class MiniJavaScanner;
}

%parse-param { MiniJavaScanner& scanner }
//%parse-param { TreeNodePtr& result }

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
%type GOAL
%type MAIN_CLASS
%type CLASS_DECLARATION
%type TYPE
%type VAR_DECLARATION
%type METHOD_DECLARATION
%type STATEMENT
*/
%type <std::shared_ptr<ExpressionBase>> expression
%type <std::vector<std::shared_ptr<ExpressionBase>>> few_expressions

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
    : type IDENTIFIER COMMA method_args
    | type IDENTIFIER

type
    : STANDARD_TYPE
    | STANDARD_TYPE L_SQ_BRACKET R_SQ_BRACKET
    | IDENTIFIER

statement
    : L_BRACE statement_sequence R_BRACE {$$ = std::make_shared<StatementBase>($2);}
    | L_BRACE R_BRACE {$$ = std::make_shared<StatementBase>();}
    | IF L_BRACKET expression R_BRACKET statement ELSE statement {$$ = std::make_shared<StatementIf>($3, $5, $7);}
    | WHILE L_BRACKET expression R_BRACKET statement {$$ = std::make_shared<StatementWhile>($3, $5);}
    | OUT L_BRACKET expression R_BRACKET SEMICOLON {$$ = std::make_shared<StatementPrint>($3);}
    | IDENTIFIER ASSIGN_OP expression SEMICOLON {$$ = std::make_shared<StatementAssign>($1, $3);}
    | IDENTIFIER L_SQ_BRACKET expression R_SQ_BRACKET ASSIGN_OP expression SEMICOLON {$$ = std::make_shared<StatementAssignContainerElement>($1, $3, $6);}

statement_sequence
    : statement {std::vector<shared_ptr<StatementBase>> array; array.push_back($1); $$ = array;}
    | statement statement_sequence {$2.push_back($1); $$ = $2;}

*/
%%

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