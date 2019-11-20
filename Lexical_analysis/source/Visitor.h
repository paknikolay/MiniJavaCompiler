#pragma once

#include "BaseNode.h"

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
};
