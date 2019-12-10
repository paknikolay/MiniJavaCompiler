#pragma once

#include "Ast/BaseNode.h"
#include "IRT/IRTNodeBase.h"

class Visitor {

public:

    int virtual Visit(ExpressionBinOp* node) = 0;
    int virtual Visit(ExpressionBool* node) = 0;
    int virtual Visit(ExpressionFunctionCall* node) = 0;
    int virtual Visit(ExpressionGetLength* node) = 0;
    int virtual Visit(ExpressionIdentifier* node) = 0;
    int virtual Visit(ExpressionIndex* node) = 0;
    int virtual Visit(ExpressionInt* node) = 0;
    int virtual Visit(ExpressionNegation* node) = 0;
    int virtual Visit(ExpressionNewIdentifier* node) = 0;
    int virtual Visit(ExpressionNewIntArray* node) = 0;
    int virtual Visit(ExpressionThis* node) = 0;

    int virtual Visit(StatementIf* node) = 0;
    int virtual Visit(StatementWhile* node) = 0;
    int virtual Visit(StatementAssign* node) = 0;
    int virtual Visit(StatementAssignContainerElement* node) = 0;
    int virtual Visit(StatementPrint* node) = 0;
    int virtual Visit(StatementSequence* node) = 0;

    int virtual Visit(Type* node) = 0;
    int virtual Visit(VarDeclaration* node) = 0;
    int virtual Visit(MethodBody* node) = 0;
    int virtual Visit(MethodDeclaration* node) = 0;
    int virtual Visit(ClassDeclaration* node) = 0;
    int virtual Visit(MainClass* node) = 0;
    int virtual Visit(Goal* node) = 0;

    int Visit(Arg* node) = 0;
    int Visit(BinOp* node) = 0;
    int Visit(Call* node) = 0;
    int Visit(Const* node) = 0;
    int Visit(ESeq* node) = 0;
    int Visit(IRTExpBase* node) = 0;
    int Visit(Local* node) = 0;
    int Visit(Mem* node) = 0;
    int Visit(Name* node) = 0;
    int Visit(Temp* node) = 0;
    int Visit(ExpList* node) = 0;
    int Visit(IRTStatementBase* node) = 0;

};
