//
// Created by malik on 26.10.2019.
//

#ifndef MINI_JAVA_COMPILER_CLASSDECLARATION_H
#define MINI_JAVA_COMPILER_CLASSDECLARATION_H

#include <string>
#include <memory>
#include <vector>
#include "../VarDeclaration/VarDeclaration.h"
#include "../MethodDeclaration/MethodDeclaration.h"
#include "../BaseNode.h"

//Вспомогательный класс
struct ClassDeclarationPrefix{
    ClassDeclarationPrefix(const std::string &className, const std::string &extends="none") :
        class_name(className),
        extends(extends)
    {}

    std::string class_name;
    std::string extends;
};

////////////////////////////////
class ClassDeclaration : public BaseNode {
public:
    ClassDeclaration(
                     const std::shared_ptr<ClassDeclarationPrefix> pref,
                     const std::vector<std::shared_ptr<VarDeclaration>>& vars,
                     const std::vector<std::shared_ptr<MethodDeclaration>>& meths=
                             std::vector<std::shared_ptr<MethodDeclaration>>()
                     ):
                        class_name(pref->class_name),
                        vars(vars),
                        methods(meths),
                        extends(pref->extends)

    {}

    ClassDeclaration(
            const std::shared_ptr<ClassDeclarationPrefix> pref,
            const std::vector<std::shared_ptr<MethodDeclaration>>& meths
    ):
            class_name(pref->class_name),
            methods(meths),
            extends(pref->extends)

    {}

    ClassDeclaration(
            const std::shared_ptr<ClassDeclarationPrefix> pref):
            class_name(pref->class_name),
            extends(pref->extends)

    {}
    const std::string &GetClassName() const {
        return class_name;
    }

    const std::string &GetExtends() const {
        return extends;
    }

    const std::vector<std::shared_ptr<VarDeclaration>> &GetVars() const {
        return vars;
    }

    const std::vector<std::shared_ptr<MethodDeclaration>> &GetMethods() const {
        return methods;
    }

    int Accept(Visitor* v);

private:
    std::string class_name;
    std::string extends;
    std::vector<std::shared_ptr<VarDeclaration>> vars;
    std::vector<std::shared_ptr<MethodDeclaration>> methods;
};



#endif //MINI_JAVA_COMPILER_CLASSDECLARATION_H
