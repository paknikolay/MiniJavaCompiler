//
// Created by Илья on 27.11.2019.
//

#include <iostream>
#include <algorithm>

#include "CheckTypeVisitor.h"


void CheckTypeVisitor::CheckTypes(const std::shared_ptr<Goal>& node)
{
    SymbolTableVisitor st_visitor(node.get());
    stg = st_visitor.GetSymbolTable();
    returns.clear();

    int res = CheckType(std::shared_ptr<Goal>(node));
    std::cerr << "Check Type: " << res << " errors." << std::endl << std::endl;
    if (res != 0) {
        throw std::logic_error("Some errors were detected while checking types.");
    }
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
    returns.push_back("<Unknown>");
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
        std::cerr << "TYPE ERROR at " << node->GetPosition().line << "." << node->GetPosition().column
                  << ": types of arguments should be the same. But they are " << returns[ret_len]
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
    std::reverse(args_types.begin(), args_types.end());
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
        std::cerr << "INVALID ARGUMENTS ERROR at " << node->GetPosition().line << "." << node->GetPosition().column
                  << ": no method " << node->GetName() << " in " << returns[ret_len] << " with arguments ";
        for (unsigned int i = ret_len + 1; i < returns.size(); ++i) {
            std::cerr << " " << returns[i];
        }
        std::cerr << std::endl;
        res += 1;
        returns[ret_len] = "<Unknown>";

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
        std::cerr << "TYPE ERROR at " << node->GetPosition().line << "." << node->GetPosition().column
                  << ": only int[] and string[] can have .length() not " << returns[ret_len] << std::endl << std::endl;
        returns[ret_len] = "int";
        return res + 1;
    }
}

int CheckTypeVisitor::Visit(ExpressionIdentifier* node)
{
    auto variables = cur_method->GetAllVariables();

    bool was_found = false;
    for (auto& v : variables) {
        if (v.first == node->GetIdentifier()) {
            returns.push_back(v.second->type_name);
            was_found = true;
            break;
        }
    }

    if (!was_found) {
        std::cerr << "TYPE ERROR at " << node->GetPosition().line << "." << node->GetPosition().column
                  << ": no such variable: " << node->GetIdentifier() << std::endl;
        return 1;
    }

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
        std::cerr << "TYPE ERROR at " << node->GetPosition().line << "." << node->GetPosition().column
                  << ": only int[] and string[] have indices not " << returns[ret_len] << std::endl << std::endl;
        returns[ret_len] = "<Unknown>";
        res += 1;
    }
    if (hasError && returns[ret_len + 1] != "int") {
        std::cerr << "TYPE ERROR at " << node->GetPosition().line << "." << node->GetPosition().column
                  << ": index must be int not " << returns[ret_len] << std::endl << std::endl;
        returns[ret_len] = "<Unknown>";
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
        std::cerr << "TYPE ERROR at " << node->GetPosition().line << "." << node->GetPosition().column
                  << ": only boolean can have negation, not " << returns[ret_len] << std::endl << std::endl;
        returns[ret_len] = "boolean";
    }

    return res;
}

int CheckTypeVisitor::Visit(ExpressionNewIdentifier* node)
{
    std::string name = node->GetIdentifier();
    bool was_found = (name == "int" || name == "bool" || name == "string" || name == "int[]" || name == "string[]");

    if (!was_found) {
        auto classes = stg->GetAllClasses();

        for (auto& cl : classes) {
            if (cl->GetName() == name) {
                cur_class = cl;
                was_found = true;
                break;
            }
        }
    }

    if (!was_found) {
        std::cerr << "TYPE ERROR at " << node->GetPosition().line << "." << node->GetPosition().column
                  << ": no such type: " << name << std::endl;
        return 1;
    }

    returns.push_back(name);
    return 0;
}

int CheckTypeVisitor::Visit(ExpressionNewIntArray* node)
{
    int ret_len = returns.size();
    int res = CheckType(node->GetCount());

    if (returns[ret_len] != "int") {
        res += 1;
        std::cerr << "TYPE ERROR at " << node->GetPosition().line << "." << node->GetPosition().column
                  << ": index must be int not " << returns[ret_len] << std::endl << std::endl;
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
        std::cerr << "TYPE ERROR at " << node->GetPosition().line << "." << node->GetPosition().column
                  << ": only boolean can be an 'if' condition, not " << returns[ret_len] << std::endl << std::endl;
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
        std::cerr << "TYPE ERROR at " << node->GetPosition().line << "." << node->GetPosition().column
                  << ": only boolean can be an 'if' condition, not " << returns[ret_len] << std::endl << std::endl;
    }
    res += CheckType(node->GetWhileStatement());

    returns.resize(ret_len);
    return res;
}

int CheckTypeVisitor::Visit(StatementAssign* node)
{
    int ret_len = returns.size();
    int res = CheckType(node->GetExpression());

    auto variables = cur_method->GetAllVariables();

    bool was_found = false;
    for (auto& v : variables) {
        if (v.first == node->GetIdentifier()) {
            if (returns[ret_len] != v.second->type_name) {
                res += 1;
                std::cerr << "TYPE ERROR at " << node->GetPosition().line << "." << node->GetPosition().column
                          << ": left and right parts of assigment have different types: "
                          << v.second->type_name << " and " << returns[ret_len] << std::endl << std::endl;
            }
            was_found = true;
            break;
        }
    }

    if (!was_found) {
        std::cerr << "TYPE ERROR at " << node->GetPosition().line << "." << node->GetPosition().column
                  << ": no such variable: " << node->GetIdentifier() << std::endl;
        res += 1;
    }

    returns.resize(ret_len);
    return res;
}

int CheckTypeVisitor::Visit(StatementAssignContainerElement* node)
{
    int ret_len = returns.size();
    int res = CheckType(node->GetExpression());

    res += CheckType(node->GetIndex());

    auto variables = cur_method->GetAllVariables();

    bool was_found = false;
    for (auto& v : variables) {
        if (v.first == node->GetIdentifier()) {
            if (v.second->type_name != "int[]") {
                res += 1;
                std::cerr << "TYPE ERROR at " << node->GetPosition().line << "." << node->GetPosition().column
                          << ": only int[] have indices not " << v.second->type_name << std::endl << std::endl;
            }
            was_found = true;
            break;
        }
    }

    if (!was_found) {
        std::cerr << "TYPE ERROR at " << node->GetPosition().line << "." << node->GetPosition().column
                  << ": no such variable: " << node->GetIdentifier() << std::endl;
        res += 1;
    }

    if (returns[ret_len + 1] != "int") {
        res += 1;
        std::cerr << "TYPE ERROR at " << node->GetPosition().line << "." << node->GetPosition().column
                  << ": index must be int not " << returns[ret_len + 1] << std::endl << std::endl;
    }
    if (returns[ret_len] != "int") {
        res += 1;
        std::cerr << "TYPE ERROR at " << node->GetPosition().line << "." << node->GetPosition().column
                  << ": left and right parts of assigment have different types: int and "
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
        std::cerr << "TYPE ERROR at " << node->GetPosition().line << "." << node->GetPosition().column
                  << ": only int, boolean or string can be printed, not "
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
    std::string name = node->getTypeName();
    bool was_found = (name == "int" || name == "bool" || name == "string" || name == "int[]" || name == "string[]");

    if (!was_found) {
        auto classes = stg->GetAllClasses();

        for (auto& cl : classes) {
            if (cl->GetName() == name) {
                cur_class = cl;
                was_found = true;
                break;
            }
        }
    }

    if (!was_found) {
        std::cerr << "TYPE ERROR at " << node->GetPosition().line << "." << node->GetPosition().column
                  << ": no such type: " << name << std::endl;
        return 1;
    }

    returns.push_back(name);
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

    auto methods = cur_class->GetAllMethods();

    bool was_found = false;
    for (auto & pair : methods) {
        if (pair.first.first != node->GetMethodName()) { continue; }
        if (args.size() != pair.first.second.size()) { continue; }

        bool has_same_args = true;
        for (unsigned int i = 0; i < args.size(); i++) {
            has_same_args &= (args[i] == pair.first.second[i]);
        }

        if (has_same_args) {
            cur_method = pair.second;
            was_found = true;
            break;
        }
    }

    if (!was_found) {
        std::cerr << "TYPE ERROR at " << node->GetPosition().line << "." << node->GetPosition().column
                  << ": no method " << node->GetMethodName() << "(";
        for (auto& arg : args) {
            std::cerr << arg << " ";
        }
        std::cerr << ") in  class " << cur_class->GetName() << std::endl;
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

    auto classes = stg->GetAllClasses();

    bool was_found = false;
    for (auto& cl : classes) {
        if (cl->GetName() == node->GetClassName()) {
            cur_class = cl;
            was_found = true;
            break;
        }
    }

    if (!was_found) {
        std::cerr << "TYPE ERROR at " << node->GetPosition().line << "." << node->GetPosition().column
                  << ": no such class: " << node->GetClassName() << std::endl;
        return res + 1;
    }

    for (auto& method : node->GetMethods()) {
        res += CheckType(method);
    }

    returns.resize(ret_len);
    return res;
}

int CheckTypeVisitor::Visit(MainClass* node)
{
    int ret_len = returns.size();

    auto classes = stg->GetAllClasses();

    bool was_found = false;
    for (auto& cl : classes) {
        if (cl->GetName() == node->GetClassName()) {
            cur_class = cl;
            was_found = true;
            break;
        }
    }

    if (!was_found) {
        std::cerr << "TYPE ERROR at " << node->GetPosition().line << "." << node->GetPosition().column
                  << ": no such class: " << node->GetClassName() << std::endl;
        return 1;
    }

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