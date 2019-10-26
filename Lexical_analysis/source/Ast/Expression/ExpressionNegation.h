//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONNEGATION_H
#define MINI_JAVA_COMPILER_EXPRESSIONNEGATION_H

#include "ExpressionBase.h"
#include <memory>

class ExpressionNegation : ExpressionBase {
public:
    explicit ExpressionNegation(std::shared_ptr<ExpressionBase> &value);

    ExpressionBase* getValue() const;

    const std::shared_ptr<ExpressionBase>& GetValue(){ return value; };

private:
    std::shared_ptr<ExpressionBase> value;
};

ExpressionNegation::ExpressionNegation(std::shared_ptr<ExpressionBase> &value_) : value(value_) {}

ExpressionBase* ExpressionNegation::getValue() const {
    return value.get();
}

#endif //MINI_JAVA_COMPILER_EXPRESSIONNEGATION_H
