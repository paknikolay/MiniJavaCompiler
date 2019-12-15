//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONBOOL_H
#define MINI_JAVA_COMPILER_EXPRESSIONBOOL_H

#include "ExpressionBase.h"

class ExpressionBool : public ExpressionBase {
public:
    ExpressionBool(std::pair<int, int> pos_, bool value) : value(value)
    {
        SetPosition(pos_);
    }

    const bool GetValue() const { return value; }
    int Accept(Visitor* v);
private:
    bool value;
};


#endif //MINI_JAVA_COMPILER_EXPRESSIONBOOL_H
