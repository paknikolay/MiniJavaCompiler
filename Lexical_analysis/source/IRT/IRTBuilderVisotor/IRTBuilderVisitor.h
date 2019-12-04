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

#include "../../SymbolTableVisitor.h"
#include "../IRTNodeBase.h"

#include "Statement/IRTStatement.h"
#include "IRTExp/IRTExp.h"
#include "../IRTExp/IRTExpBase.h"

class IRTBuilderVisitor : Visitor {
private:
    struct FuncInfo{
        std::string className;
        std::vector<std::string> argsTypes;
        std::string funcName;
        std::shared_ptr<IRTNodeBase> irtTree;

        FuncInfo(
                 const std::string& className,
                 std::vector<std::string>& argsTypes,
                 const std::string& funcName,
                 const std::shared_ptr<IRTNodeBase>& irtTree
                )
                : className(className),
                  argsTypes(argsTypes),
                  funcName(funcName),
                  irtTree(irtTree)
        {}
    };

    std::vector<FuncInfo> irtTrees;
    std::shared_ptr<IRTNodeBase> lastResult;
    std::string curClass;

    std::string curLabel = "a";
    std::string curRegister = "a";

    void updateString(std::string& str) {
        char& last_char = str.back();
        if (last_char == 'z') {
            str.push_back('a');
        } else {
            last_char++;
        }
    }
    std::string getNextRegister() {
        updateString(curRegister);
        return curRegister;

    }
    std::string getNextLabel() {
        updateString(curLabel);
        return curLabel;
    }

    void handleStatementArray(const std::vector<std::shared_ptr<StatementBase>>& array);

    std::shared_ptr<SymbolTableGlobal> symbolTable;
    std::shared_ptr<SymbolTableMethod> methodTable;

    std::shared_ptr<IRTExpBase> getAddressOfVariable(std::string identifier);

public:

    IRTBuilderVisitor(std::shared_ptr<SymbolTableGlobal> symbolTable)
    : symbolTable(symbolTable)
    {
    }

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

