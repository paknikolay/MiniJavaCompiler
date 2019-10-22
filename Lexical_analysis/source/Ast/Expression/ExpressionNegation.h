//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONNEGATION_H
#define MINI_JAVA_COMPILER_EXPRESSIONNEGATION_H

#include "ExpressionBase.h"
#include <memory>

class ExpressionNegation : ExpressionBase {
public:
    ExpressionNegation(std::unique_ptr<ExpressionBase> &value);

    const std::unique_ptr<ExpressionBase> &getValue() const;

    void setValue(std::unique_ptr<ExpressionBase> &value);

private:
    std::unique_ptr<ExpressionBase> value;
};

ExpressionNegation::ExpressionNegation(std::unique_ptr<ExpressionBase> &value_) : value(value_.release()) {}

const std::unique_ptr<ExpressionBase> &ExpressionNegation::getValue() const {
    return value;
}

void ExpressionNegation::setValue(std::unique_ptr<ExpressionBase> &value) {
    ExpressionNegation::value.reset(value.release());
}

#endif //MINI_JAVA_COMPILER_EXPRESSIONNEGATION_H
