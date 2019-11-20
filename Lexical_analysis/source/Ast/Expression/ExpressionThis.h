//
// Created by nikolai on 22.10.19.
//
#pragma once

#include "ExpressionBase.h"

class ExpressionThis : public ExpressionBase {
public:
    ExpressionThis() {}
    int Accept(Visitor* v);
};

