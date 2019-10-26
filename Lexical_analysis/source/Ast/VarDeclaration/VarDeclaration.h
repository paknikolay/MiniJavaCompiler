//
// Created by malik on 26.10.2019.
//

#ifndef MINI_JAVA_COMPILER_VARDECLARATION_H
#define MINI_JAVA_COMPILER_VARDECLARATION_H


#include <string>
#include <memory>
#include "../Type/Type.h"

class VarDeclaration {
public:
    VarDeclaration(const std::shared_ptr<Type> &type, const std::string &name) : type(type), name(name) {}

private:
    std::shared_ptr<Type> type;
    std::string name;
};


#endif //MINI_JAVA_COMPILER_VARDECLARATION_H
