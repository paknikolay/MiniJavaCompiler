//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONNEWIDENTIFIER_H
#define MINI_JAVA_COMPILER_EXPRESSIONNEWIDENTIFIER_H

#include "../Expression/ExpressionBase.h"
#include "../Expression/ExpressionIdentifier.h"
#include <memory>

class ExpressionNewIdentifier : ExpressionBase {
public:
    ExpressionNewIdentifier(std::shared_ptr<ExpressionIdentifier> &identifier) : identifier(identifier) {}

private:
    std::shared_ptr<ExpressionIdentifier> identifier;
};


#endif //MINI_JAVA_COMPILER_EXPRESSIONNEWIDENTIFIER_H
