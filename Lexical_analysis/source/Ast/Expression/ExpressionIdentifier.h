//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONIDENTIFIER_H
#define MINI_JAVA_COMPILER_EXPRESSIONIDENTIFIER_H

#include "../Expression/ExpressionBase.h"
#include <string>

class ExpressionIdentifier : public ExpressionBase {
public:
    ExpressionIdentifier(const std::string& identifier_): identifier(identifier) {}

    const std::string& GetIdentifier() const { return identifier; };

private:
    std::string identifier;
};


#endif //MINI_JAVA_COMPILER_EXPRESSIONIDENTIFIER_H
