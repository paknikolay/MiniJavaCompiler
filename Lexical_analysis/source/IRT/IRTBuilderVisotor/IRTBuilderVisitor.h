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


class IRTBuilderVisitor : Visitor {
private:

public:

    IRTNodeBase* Visit(ExpressionBinOp* node);
    IRTNodeBase* Visit(ExpressionBool* node);
    IRTNodeBase* Visit(ExpressionFunctionCall* node);
    IRTNodeBase* Visit(ExpressionGetLength* node);
    IRTNodeBase* Visit(ExpressionIdentifier* node);
    IRTNodeBase* Visit(ExpressionIndex* node);
    IRTNodeBase* Visit(ExpressionInt* node);
    IRTNodeBase* Visit(ExpressionNegation* node);
    IRTNodeBase* Visit(ExpressionNewIdentifier* node);
    IRTNodeBase* Visit(ExpressionNewIntArray* node);
    IRTNodeBase* Visit(ExpressionThis* node);

    IRTNodeBase* Visit(StatementIf* node);
    IRTNodeBase* Visit(StatementWhile* node);
    IRTNodeBase* Visit(StatementAssign* node);
    IRTNodeBase* Visit(StatementAssignContainerElement* node);
    IRTNodeBase* Visit(StatementPrint* node);
    IRTNodeBase* Visit(StatementSequence* node);

    IRTNodeBase* Visit(Type* node);
    IRTNodeBase* Visit(VarDeclaration* node);
    IRTNodeBase* Visit(MethodBody* node);
    IRTNodeBase* Visit(MethodDeclaration* node);
    IRTNodeBase* Visit(ClassDeclaration* node);
    IRTNodeBase* Visit(MainClass* node);
    IRTNodeBase* Visit(Goal* node);
};

