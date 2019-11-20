//
// Created by nikolai on 22.10.19.
//

#pragma once

#include "ExpressionBase.h"

class ExpressionInt : public ExpressionBase {
public:
    ExpressionInt(int value) : value(value) {}

    const int GetValue() const { return value; };
    int Accept(Visitor* v);
private:
    int value = 0;
};
