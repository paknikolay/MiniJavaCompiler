//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONIDENTIFIER_H
#define MINI_JAVA_COMPILER_EXPRESSIONIDENTIFIER_H

#include "ExpressionBase.h"
#include <string>

class ExpressionIdentifier : public ExpressionBase {
public:
    ExpressionIdentifier(std::pair<int, int> pos_, const std::string& identifier_): identifier(identifier_)
    {
        SetPosition(pos_);
    }

    const std::string& GetIdentifier() const { return identifier; };
    int Accept(Visitor* v);
private:
    std::string identifier;
};


#endif //MINI_JAVA_COMPILER_EXPRESSIONIDENTIFIER_H
