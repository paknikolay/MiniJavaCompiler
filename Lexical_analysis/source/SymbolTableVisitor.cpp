//
// Created by malik on 24.11.2019.
//

#include <set>
#include "SymbolTableVisitor.h"

//////////////////////////////////////////////////////
//Обрабатываем Expressions

int SymbolTableVisitor::Visit(ExpressionBinOp* node) {
    return -1;
}

int SymbolTableVisitor::Visit(ExpressionBool* node) {
    return -1;
}

int SymbolTableVisitor::Visit(ExpressionFunctionCall* node) {
    return -1;
}

int SymbolTableVisitor::Visit(ExpressionGetLength* node) {
    return -1;
}

int SymbolTableVisitor::Visit(ExpressionIdentifier* node) {
    return -1;
}

int SymbolTableVisitor::Visit(ExpressionIndex* node) {
    return -1;
}

int SymbolTableVisitor::Visit(ExpressionInt* node) {
    return -1;
}

int SymbolTableVisitor::Visit(ExpressionNegation* node) {
    return -1;
}

int SymbolTableVisitor::Visit(ExpressionNewIdentifier* node) {
    return -1;
}

int SymbolTableVisitor::Visit(ExpressionNewIntArray* node) {
    return -1;
}

int SymbolTableVisitor::Visit(ExpressionThis* node) {
    return -1;
}

//////////////////////////////////////////////////////
//Обрабатываем Statements

int SymbolTableVisitor::Visit(StatementIf* node) {
    return -1;
}

int SymbolTableVisitor::Visit(StatementWhile* node) {
    return -1;
}

int SymbolTableVisitor::Visit(StatementAssign* node) {
    return -1;
}

int SymbolTableVisitor::Visit(StatementAssignContainerElement* node) {
    return -1;
}

int SymbolTableVisitor::Visit(StatementPrint* node) {
    return -1;
}

int SymbolTableVisitor::Visit(StatementSequence* node) {
    return -1;
}

//////////////////////////////////////////////////////
//Обрабатываем всё остальное

int SymbolTableVisitor::Visit(Type* node) {
    return -1;
}

int SymbolTableVisitor::Visit(VarDeclaration* node) {
    return -1;
}

int SymbolTableVisitor::Visit(MethodBody* node) {
    int position = 0;
    for (const auto& var : node->GetVars()) {
        last_method->AddToScope(TypeScope::LOCAL_VARIABLE, var->GetName());
        last_method->AddToVariables(position, var->GetName(), GetTypeName(var->GetType()));
    }

    return 1;
}

int SymbolTableVisitor::Visit(MethodDeclaration* node)
{
    last_method = std::make_shared<SymbolTableMethod>(node->GetMethodName(), GetTypeName(node->GetReturnType()), node->GetPrivacyModifier());


    int position = 1;
    for (const auto& arg : node->GetArgs()) {
        if (!last_method->IsExist(arg.second)) {
            last_method->AddToScope(TypeScope::ARGUMENT, arg.second);
            last_method->AddToVariables(position, arg.second, GetTypeName(arg.first));
            ++position;
        } else {
            throw std::runtime_error("double argument declaration at " + node->GetPosition().ToString());
        }
    }

    node->GetMethodBody()->Accept(this);
    return 1;
}

int SymbolTableVisitor::Visit(ClassDeclaration* node) {

    last_class = std::make_shared<SymbolTableClasses>(node->GetClassName(), node->GetExtends());
    last_class->SetPosition(node->GetPosition());

    int position = 0;
    for (const auto& var : node->GetVars()) {
        last_class->AddToVariables(position, var->GetName(), GetTypeName(var->GetType()));
        ++position;
    }

    position = 0;
    for (const auto& method : node->GetMethods()) {
        method->Accept(this);

        last_method->AddToScope(TypeScope::ARGUMENT, "this");
        last_method->AddToVariables(0, "this", node->GetClassName());

        last_class->AddToMethods(position, last_method, GetTypeName(method->GetArgs()));
        ++position;
    }
    return 1;
}

int SymbolTableVisitor::Visit(MainClass* node) {

    last_class = std::make_shared<SymbolTableClasses>(node->GetClassName());

    std::shared_ptr<SymbolTableMethod> main_class_method = std::make_shared<SymbolTableMethod>("main", "void", EModifier::PUBLIC);

    main_class_method->AddToScope(TypeScope::ARGUMENT, node->GetArgsName());
    main_class_method->AddToVariables(0, "this", node->GetClassName());

    main_class_method->AddToScope(TypeScope::ARGUMENT, node->GetArgsName());
    main_class_method->AddToVariables(1, node->GetArgsName(), "String[]");

    last_class->AddToMethods(1, main_class_method, {"String[]"});

    return 1;
}

int SymbolTableVisitor::Visit(Goal* node) {
    symbol_table = std::make_shared<SymbolTableGlobal>();

    node->GetMainClass()->Accept(this);
    symbol_table->AddToVariables(last_class);

    for (const auto& class_declaration : node->GetClassDeclarations()) {
        class_declaration->Accept(this);
        symbol_table->AddToVariables(last_class);
    }

    // int, bool, int[], string

    auto simple_types = std::make_shared<SymbolTableClasses>("int[]");
    auto simple_method = std::make_shared<SymbolTableMethod>("GetLength", "int", EModifier::PUBLIC);
    simple_method->AddToVariables(0, "this", "int[]");
    simple_method->AddToScope(TypeScope::ARGUMENT, "this");

    simple_types->AddToMethods(0, simple_method, {});

    symbol_table->AddToVariables(simple_types);




    return 1;
}

SymbolTableVisitor::SymbolTableVisitor(Goal* node) {
    Visit(node);
    ImplementExtends();
}

void SymbolTableVisitor::ImplementExtends() {
    for (auto& table: symbol_table->GetAllClasses()) {
        std::set<std::string> set = {table->GetName()};
        ImplementRecursively(table, set);
    }
}

void SymbolTableVisitor::ImplementRecursively(const std::shared_ptr<SymbolTableClasses>& cur, std::set<std::string>& names_) {
    if (cur->GetExtends() != "none") {
        if (names_.find(cur->GetExtends()) != names_.end()) {
            throw std::runtime_error("recursive extendtion" + cur->GetPosition().ToString());
        }
        names_.insert(cur->GetName());
        ImplementRecursively(symbol_table->GetClass(cur->GetExtends()), names_);
        for (const auto& variable: symbol_table->GetClass(cur->GetExtends())->GetAllVariables()) {
            cur->AddToVariables(cur->GetAllVariables().size(), variable.first, variable.second->type_name);
        }

        for (const auto& variable: symbol_table->GetClass(cur->GetExtends())->GetAllMethods()) {
            cur->AddToMethods(cur->GetAllMethods().size(), variable.second, variable.first.second);
        }

        for (const auto& method: cur->GetAllMethods()) {
            for (const auto& variables: cur->GetAllVariables()) {
                method.second->AddToVariables(method.second->GetSize(), variables.first, variables.second->type_name);
                method.second->AddToScope(TypeScope::CLASS_VARIABLE, variables.first);
            }
        }
    } else {
        for (const auto& method: cur->GetAllMethods()) {
            for (const auto& variables: cur->GetAllVariables()) {
                method.second->AddToVariables(variables.second->position, variables.first, variables.second->type_name);
                method.second->AddToScope(TypeScope::CLASS_VARIABLE, variables.first);
            }
        }
    }


}
