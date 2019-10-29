//
// Created by nikolai on 22.10.19.
//

#include "ExpressionInt.h"
#include "../../DotVisitor.h"


int ExpressionInt::Accept(Visitor* v)
{
    return v->Visit(this);
}
