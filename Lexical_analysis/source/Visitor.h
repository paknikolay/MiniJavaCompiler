#pragma once

#include "IRT/IRTExp/IRTExp.h"
#include "IRT/Statement/IRTStatement.h"
#include "Ast/BaseNode.h"

#include "Ast/Expression/Expressions.h"
#include "Ast/Statement/Statements.h"
#include "Ast/Type/Type.h"
#include "Ast/VarDeclaration/VarDeclaration.h"
#include "Ast/MethodDeclaration/MethodDeclaration.h"
#include "Ast/ClassDeclaration/ClassDeclaration.h"
#include "Ast/MainClass/MainClass.h"
#include "Ast/Goal/Goal.h"

class Visitor {

public:

    int virtual Visit(ExpressionBinOp* node) {return 0;}
    int virtual Visit(ExpressionBool* node) {return 0;}
    int virtual Visit(ExpressionFunctionCall* node) {return 0;}
    int virtual Visit(ExpressionGetLength* node) {return 0;}
    int virtual Visit(ExpressionIdentifier* node) {return 0;}
    int virtual Visit(ExpressionIndex* node) {return 0;}
    int virtual Visit(ExpressionInt* node) {return 0;}
    int virtual Visit(ExpressionNegation* node) {return 0;}
    int virtual Visit(ExpressionNewIdentifier* node) {return 0;}
    int virtual Visit(ExpressionNewIntArray* node) {return 0;}
    int virtual Visit(ExpressionThis* node) {return 0;}

    int virtual Visit(StatementIf* node) {return 0;}
    int virtual Visit(StatementWhile* node) {return 0;}
    int virtual Visit(StatementAssign* node) {return 0;}
    int virtual Visit(StatementAssignContainerElement* node) {return 0;}
    int virtual Visit(StatementPrint* node) {return 0;}
    int virtual Visit(StatementSequence* node) {return 0;}

    int virtual Visit(Type* node) {return 0;}
    int virtual Visit(VarDeclaration* node) {return 0;}
    int virtual Visit(MethodBody* node) {return 0;}
    int virtual Visit(MethodDeclaration* node) {return 0;}
    int virtual Visit(ClassDeclaration* node) {return 0;}
    int virtual Visit(MainClass* node) {return 0;}
    int virtual Visit(Goal* node) {return 0;}

    int virtual Visit(Arg* node) {return 0;}
    int virtual Visit(BinOp* node) {return 0;}
    int virtual Visit(Call* node) {return 0;}
    int virtual Visit(Const* node) {return 0;}
    int virtual Visit(ESeq* node) {return 0;}
    int virtual Visit(IRTExpBase* node) {return 0;}
    int virtual Visit(Local* node) {return 0;}
    int virtual Visit(Mem* node) {return 0;}
    int virtual Visit(Name* node) {return 0;}
    int virtual Visit(Temp* node) {return 0;}
    int virtual Visit(ExpList* node) {return 0;}
    int virtual Visit(Label* node) {return 0;}
    int virtual Visit(IRTStatementBase* node) {return 0;}
    int virtual Visit(IRTNodeBase* node) {return 0;}
    int virtual Visit(Seq* node) {return 0;}
    int virtual Visit(Move* node) {return 0;}

    int virtual Visit(CJump* node){return 0;}
    int virtual Visit(Jump* node){return 0;}

};
