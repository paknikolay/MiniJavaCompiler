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
class VariableBase {
    TypeScope type;
    SimpleVariable variable;
    virtual std::shared_ptr<SymbolTableClasses> GetClassTable(const std::string&) = 0;
    virtual std::shared_ptr<SimpleVariable> GetVariable(const std::string&) = 0;
};


class SymbolTableMethod {
public:

    SymbolTableMethod(const std::string& name_) : name(name_) {

    }

    void AddToVariables(const int position, const std::shared_ptr<VarDeclaration>& variable) {
        table[variable->GetName()] = {position, variable->GetType()};
    }

    TypeScope GetVariableScope(const std::string& name_) {
        TypeScope typee ;
        return typee;
    }

    std::shared_ptr<SimpleVariable> GetVariable(const std::string& name) {
        return table[name];
    }

    std::string GetName() {
        return name;
    }


private:
    std::string name;
    std::string type_name;
    std::map<std::string, std::shared_ptr<SimpleVariable>> table;
};


class SymbolTableClasses {
public:

    SymbolTableClasses(const std::string& name_): name(name_) {

    }

    void AddToVariables(const int position, const std::shared_ptr<VarDeclaration>& variable) {
        table[variable->GetName()] = {position, variable->GetType()};
    }

    void AddToMethods(const int position, const std::shared_ptr<SymbolTableMethod>& methods) {
        methods_table[methods->GetName()] = methods;
    }


    std::shared_ptr<SimpleVariable> GetVariable(const std::string& name) {
        return table[name];
    }

    std::shared_ptr<SymbolTableMethod> GetMethod(const std::string& name, const std::vector<std::string>& variable_list) {
        methods_table[name];
    }

    std::string GetName() {
        return name;
    }


private:
    std::string name;
    std::map<std::string, std::shared_ptr<SimpleVariable>> table;
    std::map<std::string, std::shared_ptr<SymbolTableMethod>> methods_table;
};

class SymbolTableGlobal {
public:
    void AddToVariables(const std::shared_ptr<SymbolTableClasses>& class_table) {
        table[class_table->GetName()] = class_table;
    }

    std::shared_ptr<SymbolTableClasses> GetClass(const std::string& name) {
        return table[name];
    }

private:
    std::map<std::string, std::shared_ptr<SymbolTableClasses>> table;
};


struct SimpleVariable {
    int position = -1;
    std::string type_name; // int, MyClass
};


// Method_name METHOD(INT, STRING, CLASS)

#endif //MINI_JAVA_COMPILER_SYMBOLTABLE_H
