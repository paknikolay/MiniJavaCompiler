//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONNEWIDENTIFIER_H
#define MINI_JAVA_COMPILER_EXPRESSIONNEWIDENTIFIER_H

#include "ExpressionBase.h"

class ExpressionNewIdentifier : public ExpressionBase {
public:
    ExpressionNewIdentifier(std::pair<int, int> pos_, const std::string& identifier) : identifier(identifier)
    {
        SetPosition(pos_);
    }

    const std::string &GetIdentifier() const {
        return identifier;
    }

    int Accept(Visitor* v);
private:
    std::string identifier;
};


#endif //MINI_JAVA_COMPILER_EXPRESSIONNEWIDENTIFIER_H
