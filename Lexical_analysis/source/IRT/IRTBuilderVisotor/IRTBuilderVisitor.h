#pragma once

#include "Ast/Expression/Expressions.h"
#include "Ast/Statement/Statements.h"
#include "Ast/Type/Type.h"
#include "Ast/VarDeclaration/VarDeclaration.h"
#include "Ast/MethodDeclaration/MethodDeclaration.h"
#include "Ast/ClassDeclaration/ClassDeclaration.h"
#include "Ast/MainClass/MainClass.h"
#include "Ast/Goal/Goal.h"
#include "Visitor.h"

#include "SymbolTable/SymbolTable.h"
#include "../IRTNodeBase.h"

#include "../IRTExp/IRTExpBase.h"

class ExpList {
private:
    std::shared_ptr<IRTExpBase> head = nullptr;
    std::shared_ptr<ExpList> tail = nullptr;
public:
    ExpList(std::shared_ptr<IRTExpBase> head, std::shared_ptr<ExpList> tail) : head(head), tail(tail) {}
};

class StmList {
private:
    std::shared_ptr<IRTStatementBase> head = nullptr;
    std::shared_ptr<StmList> tail = nullptr;
public:
    ExpList(std::shared_ptr<IRTStatementBase> head, std::shared_ptr<StmList> tail) : head(head), tail(tail) {}
};


class IRTBuilderVisitor : Visitor {
private:
    std::shared_ptr<IRTNodeBase> lastResult;
public:

    int Visit(ExpressionBinOp* node);
    int Visit(ExpressionBool* node);
    int Visit(ExpressionFunctionCall* node);
    int Visit(ExpressionGetLength* node);
    int Visit(ExpressionIdentifier* node);
    int Visit(ExpressionIndex* node);
    int Visit(ExpressionInt* node);
    int Visit(ExpressionNegation* node);
    int Visit(ExpressionNewIdentifier* node);
    int Visit(ExpressionNewIntArray* node);
    int Visit(ExpressionThis* node);

    int Visit(StatementIf* node);
    int Visit(StatementWhile* node);
    int Visit(StatementAssign* node);
    int Visit(StatementAssignContainerElement* node);
    int Visit(StatementPrint* node);
    int Visit(StatementSequence* node);

    int Visit(Type* node);
    int Visit(VarDeclaration* node);
    int Visit(MethodBody* node);
    int Visit(MethodDeclaration* node);
    int Visit(ClassDeclaration* node);
    int Visit(MainClass* node);
    int Visit(Goal* node);
};

