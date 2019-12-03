//
// Created by malik on 24.11.2019.
//

#ifndef MINI_JAVA_COMPILER_SYMBOLTABLEVISITOR_H
#define MINI_JAVA_COMPILER_SYMBOLTABLEVISITOR_H


#include <SymbolTable/SymbolTable.h>
#include "Ast/Expression/Expressions.h"
#include "Ast/Statement/Statements.h"
#include "Ast/Type/Type.h"
#include "Ast/VarDeclaration/VarDeclaration.h"
#include "Ast/MethodDeclaration/MethodDeclaration.h"
#include "Ast/ClassDeclaration/ClassDeclaration.h"
#include "Ast/MainClass/MainClass.h"
#include "Ast/Goal/Goal.h"
#include "Visitor.h"

class SymbolTableVisitor : public Visitor {
public:

    SymbolTableVisitor(Goal* node);

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


    std::shared_ptr<SymbolTableGlobal> GetSymbolTable() {
        return symbol_table;
    }

private:
    void ImplementExtends();
    void ImplementRecursively(std::shared_ptr<SymbolTableClasses> cur);

    std::shared_ptr<SymbolTableGlobal> symbol_table;

    //bool is_last_method = false;
    std::shared_ptr<SymbolTableMethod> last_method;
    //std::string last_name;

    std::shared_ptr<SymbolTableClasses> last_class;
};


#endif //MINI_JAVA_COMPILER_SYMBOLTABLEVISITOR_H
