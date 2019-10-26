//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONNEGATION_H
#define MINI_JAVA_COMPILER_EXPRESSIONNEGATION_H

#include "ExpressionBase.h"
#include <memory>

class ExpressionNegation : ExpressionBase {
public:
    explicit ExpressionNegation(std::unique_ptr<ExpressionBase> &value);

    ExpressionBase* getValue() const;

    void setValue(std::unique_ptr<ExpressionBase> &uniquePtr);

private:
    std::unique_ptr<ExpressionBase> value;
};

ExpressionNegation::ExpressionNegation(std::unique_ptr<ExpressionBase> &value_) : value(value_.release()) {}

ExpressionBase* ExpressionNegation::getValue() const {
    return value.get();
}

void ExpressionNegation::setValue(std::unique_ptr<ExpressionBase> &uniquePtr) {
    ExpressionNegation::value = std::move(uniquePtr);
}

#endif //MINI_JAVA_COMPILER_EXPRESSIONNEGATION_H
