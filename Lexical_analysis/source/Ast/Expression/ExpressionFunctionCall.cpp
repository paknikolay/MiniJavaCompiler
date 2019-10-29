//
// Created by nikolai on 22.10.19.
//

#include "ExpressionFunctionCall.h"
#include "../../DotVisitor.h"


int ExpressionFunctionCall::Accept(Visitor* v)
{
    return v->Visit(this);
}
