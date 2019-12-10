//
// Created by Илья on 27.11.2019.
//

#include <iostream>

#include "CheckTypeVisitor.h"


void CheckTypeVisitor::CheckTypes(std::shared_ptr<Goal> node)
{
    SymbolTableVisitor st_visitor(node.get());
    stg = st_visitor.GetSymbolTable();
    returns.clear();

    int res = CheckType(std::shared_ptr<Goal>(node));
    std::cerr << "Check Type: " << res << " errors." << std::endl << std::endl;
}

int CheckTypeVisitor::CheckType(const std::shared_ptr<BaseNode>& node)
{
    if (node) {
        return node->Accept(this);
    } else {
        return VisitEmpty();
    }
}

int CheckTypeVisitor::VisitEmpty()
{
    returns.push_back("unknown");
    return 1;
}

bool CheckTypeVisitor::isElementary(const std::string& type)
{
    return type == "int" || type == "boolean" || type == "string" || type == "String[]";
}

bool CheckTypeVisitor::isArray(const std::string& type)
{
    return type == "int[]" || type == "string[]";
}

bool CheckTypeVisitor::canCast(const std::string& castingType, const std::string& typeToCast) {
    if (castingType == typeToCast){
        return true;
    }
    // Проверяем каст к базе
    auto classInfo = stg->GetClass(castingType);
    while (classInfo->GetExtends() != "none") {
        if (classInfo->GetExtends() == typeToCast) {
            return true;
        }
        classInfo = stg->GetClass(classInfo->GetExtends());
    }
    return false;
}

//////////////////////////////////////////////////////
//Обрабатываем Expressions

int CheckTypeVisitor::Visit(ExpressionBinOp* node)
{
    int res = 0;
    int ret_len = returns.size();

    res += CheckType(node->GetLeft());
    res += CheckType(node->GetRight());
    int op_value = static_cast<int>(node->GetBinOp());
    int res1 = 1 - int(returns[ret_len] == returns[ret_len + 1] && isElementary(returns[ret_len]) &&
            // Строки можно только складывать и сравнивать
            ((op_value == 0 || op_value > 6) || returns[ret_len] == "int" || returns[ret_len] == "boolean"));
    res += res1;

    if (res1) {
        std::cerr << "TYPE ERROR: types of arguments are " << returns[ret_len]
                  << " and " << returns[ret_len + 1] << std::endl << std::endl;
    }

    //magic const
    if (op_value >= 7) {
        returns[ret_len] = "boolean";
    }
    returns.resize(ret_len + 1);
    return res;
}

int CheckTypeVisitor::Visit(ExpressionBool* node)
{
    returns.push_back("boolean");
    return 0;
}

int CheckTypeVisitor::Visit(ExpressionFunctionCall* node)
{
    int res = 0;
    int ret_len = returns.size();
    res += CheckType(node->GetObject());
    for (auto& arg : node->GetArgs()) {
        res += CheckType(arg);
    }

    std::vector<std::string> args_types(returns.begin() + ret_len + 1, returns.end());
    std::shared_ptr<SymbolTableMethod> method(nullptr);
    std::vector< std::vector<std::string> > variants;
    auto methods = stg->GetClass(returns[ret_len])->GetAllMethods();

    for (auto & pair : methods) {
        if (pair.first.first != node->GetName()) { continue; }
        variants.push_back(pair.first.second);
        if (args_types.size() != pair.first.second.size()) { continue; }

        bool canCall = true;
        for (unsigned int i = 0; i < args_types.size(); i++) {
            canCall &= canCast(args_types[i], pair.first.second[i]);
        }

        if (canCall) {
            //считаем, что такая функция всего лишь одна,
            // если была бы не одна, то нужно как-то отранжировать их и выбрать наиболее подходящую
            method = stg->GetClass(returns[ret_len])->GetMethod(node->GetName(), pair.first.second);
            break;
        }
    }

    if (method != nullptr) {
        returns[ret_len] = method->GetTypeName();
    } else {
        std::cerr << "INVALID ARGUMENTS ERROR: no method " << node->GetName()
                  << " in " << returns[ret_len] << " with arguments ";
        for (unsigned int i = ret_len + 1; i < returns.size(); ++i) {
            std::cerr << " " << returns[i];
        }
        std::cerr << std::endl;
        res += 1;
        returns[ret_len] = "unknown";

        if (!variants.empty()) {
            std::cerr << "May be there should have been one of the following functions:" << std::endl;
            for (auto& args : variants) {
                std::cerr << node->GetName() << "(";
                for (auto& arg : args) {
                    std::cerr << arg << ", ";
                }
                std::cerr << ")" << std::endl;
            }
        }
        std::cerr << std::endl;
    }

    returns.resize(ret_len + 1);
    return res;
}

int CheckTypeVisitor::Visit(ExpressionGetLength* node)
{
    int res = 0;
    int ret_len = returns.size();

    res += CheckType(node->GetContainer());
    if (isArray(returns[ret_len])) {
        returns[ret_len] = "int";
        return res;
    } else {
        std::cerr << "TYPE ERROR: only int[] and string[] can have .length() not " << returns[ret_len] << std::endl << std::endl;
        returns[ret_len] = "int";
        return res + 1;
    }
}

int CheckTypeVisitor::Visit(ExpressionIdentifier* node)
{
    returns.push_back(cur_method->GetVariable(node->GetIdentifier())->type_name);
    return 0;
}

int CheckTypeVisitor::Visit(ExpressionIndex* node)
{
    int res = 0;
    int ret_len = returns.size();

    res += CheckType(node->GetArray());
    res += CheckType(node->GetIndex());
    bool hasError = true;
    if (isArray(returns[ret_len]) && returns[ret_len + 1] == "int") {
        hasError = false;
        returns[ret_len] = returns[ret_len].substr(0, returns[ret_len].length() - 2);
    } else if (!isArray(returns[ret_len])) {
        std::cerr << "TYPE ERROR: only int[] and string[] have indices not " << returns[ret_len] << std::endl << std::endl;
        returns[ret_len] = "unknown";
        res += 1;
    }
    if (hasError && returns[ret_len + 1] != "int") {
        std::cerr << "TYPE ERROR: index must be int not " << returns[ret_len] << std::endl << std::endl;
        returns[ret_len] = "unknown";
        res += 1;
    }

    returns.resize(ret_len + 1);
    return res;
}

int CheckTypeVisitor::Visit(ExpressionInt* node)
{
    returns.push_back("int");
    return 0;
}

int CheckTypeVisitor::Visit(ExpressionNegation* node)
{
    int ret_len = returns.size();
    int res = CheckType(node->GetValue());

    if (returns[ret_len] != "boolean") {
        res += 1;
        std::cerr << "TYPE ERROR: only bool can have negation, not " << returns[ret_len] << std::endl << std::endl;
        returns[ret_len] = "boolean";
    }

    return res;
}

int CheckTypeVisitor::Visit(ExpressionNewIdentifier* node)
{
    returns.push_back(node->GetIdentifier());
    return 0;
}

int CheckTypeVisitor::Visit(ExpressionNewIntArray* node)
{
    int ret_len = returns.size();
    int res = CheckType(node->GetCount());

    if (returns[ret_len] != "int") {
        res += 1;
        std::cerr << "TYPE ERROR: index must be int not " << returns[ret_len] << std::endl << std::endl;
    }

    returns[ret_len] = "int[]";
    return res;
}

int CheckTypeVisitor::Visit(ExpressionThis* node)
{
    returns.push_back(cur_class->GetName());
    return 0;
}

//////////////////////////////////////////////////////
//Обрабатываем Statements

int CheckTypeVisitor::Visit(StatementIf* node)
{
    int ret_len = returns.size();
    int res = CheckType(node->GetIfExpression());

    if (returns[ret_len] != "boolean") {
        res += 1;
        std::cerr << "TYPE ERROR: only bool can be an 'if' condition, not " << returns[ret_len] << std::endl << std::endl;
    }
    res += CheckType(node->GetIfStatement());
    res += CheckType(node->GetElseStatement());

    returns.resize(ret_len);
    return res;
}

int CheckTypeVisitor::Visit(StatementWhile* node)
{
    int ret_len = returns.size();
    int res = CheckType(node->GetWhileExpression());

    if (returns[ret_len] != "boolean") {
        res += 1;
        std::cerr << "TYPE ERROR: only boolean can be an 'if' condition, not " << returns[ret_len] << std::endl << std::endl;
    }
    res += CheckType(node->GetWhileStatement());

    returns.resize(ret_len);
    return res;
}

int CheckTypeVisitor::Visit(StatementAssign* node)
{
    int ret_len = returns.size();
    int res = CheckType(node->GetExpression());

    std::string identifier = cur_method->GetVariable(node->GetIdentifier())->type_name;
    if (returns[ret_len] != identifier) {
        res += 1;
        std::cerr << "TYPE ERROR: left and right parts of assigment have different types: "
                  << identifier << " and " << returns[ret_len] << std::endl << std::endl;
    }

    returns.resize(ret_len);
    return res;
}

int CheckTypeVisitor::Visit(StatementAssignContainerElement* node)
{
    int ret_len = returns.size();
    int res = CheckType(node->GetExpression());

    res += CheckType(node->GetIndex());
    std::string identifier = cur_method->GetVariable(node->GetIdentifier())->type_name;
    if (returns[ret_len + 1] != "int") {
        res += 1;
        std::cerr << "TYPE ERROR: index must be int not " << returns[ret_len + 1] << std::endl << std::endl;
    }
    if (identifier != "int[]") {
        res += 1;
        std::cerr << "TYPE ERROR: only int[] have indices not " << identifier << std::endl << std::endl;
    }
    if (returns[ret_len] != "int") {
        res += 1;
        std::cerr << "TYPE ERROR: left and right parts of assigment have different types: int and "
                  << returns[ret_len] << std::endl << std::endl;
    }

    returns.resize(ret_len);
    return res;
}

int CheckTypeVisitor::Visit(StatementPrint* node)
{
    int ret_len = returns.size();
    int res = CheckType(node->GetExpression());
    if (!isElementary(returns[ret_len])) {
        res += 1;
        std::cerr << "TYPE ERROR: only int, boolean or string can be printed, not "
        << returns[ret_len] << std::endl << std::endl;
    }
    returns.resize(ret_len);
    return res;
}

int CheckTypeVisitor::Visit(StatementSequence* node)
{
    int res = 0;
    int ret_len = returns.size();
    for (auto& st : node->GetArray()) {
        res += CheckType(st);
    }
    returns.resize(ret_len);
    return res;
}

//////////////////////////////////////////////////////
//Обрабатываем всё остальное

int CheckTypeVisitor::Visit(Type* node)
{
    returns.push_back(node->getTypeName());
    return 0;
}

int CheckTypeVisitor::Visit(VarDeclaration* node)
{
    int ret_len = returns.size();
    int res = CheckType(node->GetType());
    returns.resize(ret_len);
    return res;
}

int CheckTypeVisitor::Visit(MethodBody* node)
{
    int ret_len = returns.size();
    int res = 0;

    for (auto& var : node->GetVars()) {
        res += CheckType(var);
    }
    for (auto& st : node->GetStatements()) {
        res += CheckType(st);
    }
    res += CheckType(node->GetReturnExpr());

    returns.resize(ret_len);
    return res;
}

int CheckTypeVisitor::Visit(MethodDeclaration* node)
{
    int ret_len = returns.size();
    int res = 0;

    res += CheckType(node->GetReturnType());

    std::vector<std::string> args;
    for (auto& arg : node->GetArgs()) {
        res += CheckType(arg.first);
        args.push_back(returns[returns.size() - 1]);
    }

    cur_method = cur_class->GetMethod(node->GetMethodName(), args);
    res += CheckType(node->GetMethodBody());

    returns.resize(ret_len);
    return res;
}

int CheckTypeVisitor::Visit(ClassDeclaration* node)
{
    int ret_len = returns.size();
    int res = 0;

    for (auto& var : node->GetVars()) {
        res += CheckType(var);
    }

    cur_class = stg->GetClass(node->GetClassName());
    for (auto& method : node->GetMethods()) {
        res += CheckType(method);
    }

    returns.resize(ret_len);
    return res;
}

int CheckTypeVisitor::Visit(MainClass* node)
{
    int ret_len = returns.size();

    cur_class = stg->GetClass(node->GetClassName());
    cur_method = cur_class->GetMethod("main", {"String[]"});
    int res = CheckType(node->GetStatement());

    returns.resize(ret_len);
    return res;
}

int CheckTypeVisitor::Visit(Goal* node)
{
    int res = CheckType(node->GetMainClass());
    for (auto& cl : node->GetClassDeclarations()) {
        res += CheckType(cl);
    }
    return res;
}