//
// Created by malik on 26.10.2019.
//

#ifndef MINI_JAVA_COMPILER_VARDECLARATION_H
#define MINI_JAVA_COMPILER_VARDECLARATION_H


#include <string>
#include <memory>
#include "../Type/Type.h"
#include "../BaseNode.h"

class VarDeclaration : public BaseNode {
public:
    VarDeclaration(const std::shared_ptr<Type> &type_, const std::string &name_) : type(type_), name(name_) {}

    const std::shared_ptr<Type> &GetType() const {
        return type;
    }

    const std::string &GetName() const {
        return name;
    }

private:
    std::shared_ptr<Type> type;
    std::string name;
};


#endif //MINI_JAVA_COMPILER_VARDECLARATION_H
