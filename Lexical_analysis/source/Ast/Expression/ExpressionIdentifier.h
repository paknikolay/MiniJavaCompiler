//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONIDENTIFIER_H
#define MINI_JAVA_COMPILER_EXPRESSIONIDENTIFIER_H

#include "../Expression/ExpressionBase.h"
#include <memory>

class ExpressionIdentifier : ExpressionBase {

private:
    std::unique_ptr<ExpressionBase> identifier;
};


#endif //MINI_JAVA_COMPILER_EXPRESSIONIDENTIFIER_H
