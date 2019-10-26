//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONBOOL_H
#define MINI_JAVA_COMPILER_EXPRESSIONBOOL_H

#include "Expression/ExpressionBase.h"

class ExpressionBool : public ExpressionBase {
public:
    ExpressionBool(bool value) : value(value) {}

private:
    bool value;
};


#endif //MINI_JAVA_COMPILER_EXPRESSIONBOOL_H
