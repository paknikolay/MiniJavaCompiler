//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONNEGATION_H
#define MINI_JAVA_COMPILER_EXPRESSIONNEGATION_H

#include "ExpressionBase.h"

class ExpressionNegation : public ExpressionBase {
public:
    explicit ExpressionNegation(std::pair<int, int> pos_, const std::shared_ptr<ExpressionBase> &value) : value(value)
    {
        SetPosition(pos_);
    }

    const std::shared_ptr<ExpressionBase>& GetValue() const { return value; };
    int Accept(Visitor* v);

private:
    std::shared_ptr<ExpressionBase> value;
};

#endif //MINI_JAVA_COMPILER_EXPRESSIONNEGATION_H
