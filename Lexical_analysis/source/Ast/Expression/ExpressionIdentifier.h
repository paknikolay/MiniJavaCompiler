//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONIDENTIFIER_H
#define MINI_JAVA_COMPILER_EXPRESSIONIDENTIFIER_H

#include "../Expression/ExpressionBase.h"
#include <memory>

class ExpressionIdentifier : ExpressionBase {
public:
    ExpressionIdentifier(const std::shared_ptr<ExpressionBase> &identifier) : identifier(identifier) {}

    const std::shared_ptr<ExpressionBase>& GetIdentifier(){ return identifier; };

private:
    std::shared_ptr<ExpressionBase> identifier;
};


#endif //MINI_JAVA_COMPILER_EXPRESSIONIDENTIFIER_H
