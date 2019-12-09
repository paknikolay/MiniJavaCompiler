//
// Created by Илья on 27.11.2019.
//

#ifndef UNTITLED_CHECKTYPEVISITOR_H
#define UNTITLED_CHECKTYPEVISITOR_H

#pragma once

#include <fstream>
#include <vector>

#include "Ast/Expression/Expressions.h"
#include "Ast/Statement/Statements.h"
#include "Ast/Type/Type.h"
#include "Ast/VarDeclaration/VarDeclaration.h"
#include "Ast/MethodDeclaration/MethodDeclaration.h"
#include "Ast/ClassDeclaration/ClassDeclaration.h"
#include "Ast/MainClass/MainClass.h"
#include "Ast/Goal/Goal.h"

#include "SymbolTableVisitor.h"
#include "SymbolTable/SymbolTable.h"

#include "Visitor.h"


class CheckTypeVisitor : Visitor {
private:
    std::shared_ptr<SymbolTableGlobal> stg;
    std::shared_ptr<SymbolTableClasses> cur_class;
    std::shared_ptr<SymbolTableMethod> cur_method;
    std::vector<std::string> returns;

private:
    int CheckType(const std::shared_ptr<BaseNode>& node);
    int VisitEmpty();
    bool isElementary(const std::string& type);
    bool isArray(const std::string& type);
    bool canCast(const std::string& castingType, const std::string& typeToCast);

public:
    void CheckTypes(Goal* node);

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


#endif //UNTITLED_CHECKTYPEVISITOR_H
