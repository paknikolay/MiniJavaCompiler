//
// Created by nikolai on 22.10.19.
//

#pragma once

#include "ExpressionBase.h"

#include <memory>

class ExpressionGetLength : public ExpressionBase{
public:
    ExpressionGetLength(const std::shared_ptr<ExpressionBase> &container) : container(container) {}

    const std::shared_ptr<ExpressionBase>& GetContainer() const { return container; };
    int Accept(Visitor* v);
private:
    std::shared_ptr<ExpressionBase> container;
};

