//
// Created by nikolai on 22.10.19.
//
#pragma once

#include <memory>
#include "ExpressionBase.h"

class ExpressionIndex :public ExpressionBase {
public:
    ExpressionIndex(const std::shared_ptr<ExpressionBase> &array, const std::shared_ptr<ExpressionBase> &index) : array(
            array), index(index) {}

    const std::shared_ptr<ExpressionBase>& GetArray() const { return array; };
    const std::shared_ptr<ExpressionBase>& GetIndex() const { return index; };
    int Accept(Visitor* v);
private:
    std::shared_ptr<ExpressionBase> array;
    std::shared_ptr<ExpressionBase> index;
};

