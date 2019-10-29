//
// Created by nikolai on 22.10.19.
//

#include "ExpressionBinOp.h"
#include "../../DotVisitor.h"


int ExpressionBinOp::Accept(Visitor* v)
{
    return v->Visit(this);
}
