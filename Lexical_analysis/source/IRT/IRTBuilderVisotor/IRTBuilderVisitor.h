#pragma once

#include "../Ast/Expression/Expressions.h"
#include "../Ast/Statement/Statements.h"
#include "../Ast/Type/Type.h"
#include "../Ast/VarDeclaration/VarDeclaration.h"
#include "../Ast/MethodDeclaration/MethodDeclaration.h"
#include "../Ast/ClassDeclaration/ClassDeclaration.h"
#include "../Ast/MainClass/MainClass.h"
#include "../Ast/Goal/Goal.h"
#include "../Visitor.h"

//#include "../SymbolTable/SymbolTable.h"
#include "../IRTNodeBase.h"

#include "../IRTExp/IRTExpBase.h"

class IRTBuilderVisitor : Visitor {
private:
    std::shared_ptr<IRTNodeBase> lastResult;
    std::string curLabel = "a";
    std::string getNextLabel(){
        char& last_char = curLabel.back();
        if (last_char == 'z') {
            curLabel.push_back('a');
        } else {
            last_char++;
        }

        return curLabel;
    }
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

