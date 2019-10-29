//
// Created by nikolai on 22.10.19.
//

#include "ExpressionFunctionCall.h"
#include "../../Visitor.h"


int ExpressionFunctionCall::Accept(Visitor* v)
{
    return v->Visit(this);
}
