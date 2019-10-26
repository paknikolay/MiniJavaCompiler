//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONINT_H
#define MINI_JAVA_COMPILER_EXPRESSIONINT_H

#include "../Expression/ExpressionBase.h"

class ExpressionInt : public ExpressionBase {
public:
    ExpressionInt(int value) : value(value) {}

private:
    int value = 0;
};


#endif //MINI_JAVA_COMPILER_EXPRESSIONINT_H
