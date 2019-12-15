//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONINT_H
#define MINI_JAVA_COMPILER_EXPRESSIONINT_H

#include "ExpressionBase.h"

class ExpressionInt : public ExpressionBase {
public:
    ExpressionInt(std::pair<int, int> pos_, int value) : value(value)
    {
        SetPosition(pos_);
    }

    const int GetValue() const { return value; };
    int Accept(Visitor* v);
private:
    int value = 0;
};


#endif //MINI_JAVA_COMPILER_EXPRESSIONINT_H
