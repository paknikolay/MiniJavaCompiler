//
// Created by nikolai on 22.10.19.
//

#include "ExpressionBase.h"

class ExpressionBool : public ExpressionBase {
public:
    ExpressionBool(bool value) : value(value) {}

    const bool GetValue() const { return value; }
    int Accept(Visitor* v);
private:
    bool value;
};


#pragma once
