//
// Created by Илья on 27.10.2019.
//

#ifndef MINI_JAVA_COMPILER_DOTVISITOR_H
#define MINI_JAVA_COMPILER_DOTVISITOR_H

#pragma once

#include <fstream>

#include "Ast/Expression/Expressions.h"
#include "Ast/Statement/Statements.h"
#include "Ast/Type/Type.h"
#include "Ast/VarDeclaration/VarDeclaration.h"
#include "Ast/MethodDeclaration/MethodDeclaration.h"
#include "Ast/ClassDeclaration/ClassDeclaration.h"
#include "Ast/MainClass/MainClass.h"
#include "Ast/Goal/Goal.h"

#include "Visitor.h"
/* 
   Вот здесь можно проверить результат:
   https://graphs.grevian.org/graph/4950567682048000
*/
class DotVisitor : Visitor {
private:
    int n = 0;          // Номер вершины при обходе.
    std::ofstream f;    // Файл, в который будет печататься дерево.

private:
    int DrawSubtree(const std::shared_ptr<BaseNode>& node);
    int VisitEmpty();

public:
    void DrawTree(const std::shared_ptr<BaseNode>& node, const std::string& filename);

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


#endif //MINI_JAVA_COMPILER_DOTVISITOR_H
