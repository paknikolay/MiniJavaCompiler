//
// Created by nikolai on 22.10.19.
//

#include "ExpressionBinOp.h"
#include "../../Visitor.h"


int ExpressionBinOp::Accept(Visitor* v)
{
    return v->Visit(this);
}
