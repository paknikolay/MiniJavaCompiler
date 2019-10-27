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


class ClassDeclaration : public BaseNode {
public:
    ClassDeclaration(const std::string& name, const std::vector<std::shared_ptr<VarDeclaration>>& varabs,
                     const std::vector<std::shared_ptr<MethodDeclaration>>& meths, const std::string extend = "none") :
    class_name(name), vars(varabs), methods(meths), extends(extend) {}

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

private:
    std::string class_name;
    std::string extends;
    std::vector<std::shared_ptr<VarDeclaration>> vars;
    std::vector<std::shared_ptr<MethodDeclaration>> methods;
};


#endif //MINI_JAVA_COMPILER_CLASSDECLARATION_H
