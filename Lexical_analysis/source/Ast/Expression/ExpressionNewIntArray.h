//
// Created by nikolai on 22.10.19.
//
#pragma once

#include "ExpressionBase.h"
#include <memory>

class ExpressionNewIntArray : public ExpressionBase {
public:
    ExpressionNewIntArray(const std::shared_ptr<ExpressionBase> &count) : count(count) {}

    const std::shared_ptr<ExpressionBase> &GetCount() const {
        return count;
    }

    int Accept(Visitor* v);
private:
    std::shared_ptr<ExpressionBase> count;
};
