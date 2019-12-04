//
// Created by malik on 24.11.2019.
//

#ifndef MINI_JAVA_COMPILER_SYMBOLTABLE_H
#define MINI_JAVA_COMPILER_SYMBOLTABLE_H

#include <memory>
#include <map>
#include <vector>
#include "../Ast/VarDeclaration/VarDeclaration.h"
#include "../Enums.h"

class SymbolTableClasses;
struct SimpleVariable;
struct Method;

// API

inline std::string GetTypeName(const std::shared_ptr<Type>& type) {
    return type->getTypeName();
}

inline std::vector<std::string> GetTypeName(const std::vector<std::pair<std::shared_ptr<Type>, std::string>>& args) {
    std::vector<std::string> types;
    for (const auto& type: args) {
        types.push_back(GetTypeName(type.first));
    }
    return types;
}

class SymbolTableMethod {
public:

    SymbolTableMethod(const std::string& name_, const std::shared_ptr<Type>& type) : name(name_),
    type_name(::GetTypeName(type))
    {

    }

    SymbolTableMethod(const std::string& name_, const std::string& type) : name(name_), type_name(type)
    {

    }

    void AddToVariables(const int position, const std::shared_ptr<VarDeclaration>& var) {
        table[var->GetName()] = std::make_shared<SimpleVariable>(position, ::GetTypeName(var->GetType()));
    }

    void AddToVariables(const int position, const std::string& name_, const std::string& var) {
        table[name_] = std::make_shared<SimpleVariable>(position, var);
    }

    void AddToScope(const TypeScope& typeScope, const std::shared_ptr<VarDeclaration>& var) {
        table_scope[var->GetName()] = typeScope;
    }

    void AddToScope(const TypeScope& typeScope, const std::string& var) {
        table_scope[var] = typeScope;
    }

    TypeScope GetVariableScope(const std::string& name_) {
        return table_scope[name_];
    }

    std::shared_ptr<SimpleVariable> GetVariable(const std::string& name_) {
        return table[name_];
    }

    std::string GetName() {
        return name;
    }

    std::string GetTypeName() {
        return type_name;
    }

private:
    std::string name;
    std::string type_name;
    std::map<std::string, std::shared_ptr<SimpleVariable>> table;
    std::map<std::string, TypeScope > table_scope;
};


class SymbolTableClasses {
public:
    SymbolTableClasses(const std::string& name_, const std::string& extends_ = "none"): name(name_),
        extends(extends_)
    {

    }

    void AddToVariables(const int position, const std::shared_ptr<VarDeclaration>& var) {
        table[var->GetName()] = std::make_shared<SimpleVariable>(position, GetTypeName(var->GetType()));
    }

    void AddToVariables(const int position, const std::string& name_, const std::string& var) {
        table[name_] = std::make_shared<SimpleVariable>(position, var);
    }

    void AddToMethods(const int position, const std::shared_ptr<SymbolTableMethod>& methods, const std::vector<std::string>& variable_list) {
        methods_table[std::make_pair(methods->GetName(), variable_list)] = methods;
    }


    std::shared_ptr<SimpleVariable> GetVariable(const std::string& name_) {
        return table[name_];
    }

    std::shared_ptr<SymbolTableMethod> GetMethod(const std::string& name_, const std::vector<std::string>& variable_list) {
        return methods_table[std::make_pair(name_, variable_list)];
    }

    std::string GetName() {
        return name;
    }

    const std::string& GetExtends() const {
        return extends;
    }

    int GetSize() const {
        return (table. size() + (extends != "none")) * 4;  // size is 4 byte
    }

    std::map<std::string, std::shared_ptr<SimpleVariable>> GetAllVariables() {
        return table;
    }

    std::map<std::pair<std::string, std::vector<std::string>>, std::shared_ptr<SymbolTableMethod>> GetAllMethods() {
        return methods_table;
    }

private:
    std::string extends = "none";
    std::string name;
    std::map<std::string, std::shared_ptr<SimpleVariable>> table;
    std::map<std::pair<std::string, std::vector<std::string>>, std::shared_ptr<SymbolTableMethod>> methods_table;
};

class SymbolTableGlobal {
public:
    void AddToVariables(const std::shared_ptr<SymbolTableClasses>& class_table) {
        table[class_table->GetName()] = class_table;
    }

    std::shared_ptr<SymbolTableClasses> GetClass(const std::string& name) {
        return table[name];
    }

    std::vector<std::shared_ptr<SymbolTableClasses>> GetAllClasses() {
        std::vector<std::shared_ptr<SymbolTableClasses>> answer;
        for (auto& clas : table) {
            answer.push_back(clas.second);
        }
        return  answer;
    }

private:
    std::map<std::string, std::shared_ptr<SymbolTableClasses>> table;
};


struct SimpleVariable {
    int position = -1;
    std::string type_name; // int, MyClass

    SimpleVariable(int pos, const std::string& name): position(pos), type_name(name) {

    }
};


// Method_name METHOD(INT, STRING, CLASS)

#endif //MINI_JAVA_COMPILER_SYMBOLTABLE_H
