//
// Created by nikolai on 22.10.19.
//

#pragma once

#include "ExpressionBase.h"

class ExpressionNegation : public ExpressionBase {
public:
    explicit ExpressionNegation(const std::shared_ptr<ExpressionBase> &value) : value(value) {}

    const std::shared_ptr<ExpressionBase>& GetValue() const { return value; };
    int Accept(Visitor* v);

private:
    std::shared_ptr<ExpressionBase> value;
};
