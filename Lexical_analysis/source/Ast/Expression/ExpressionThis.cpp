//
// Created by nikolai on 22.10.19.
//

#include "ExpressionThis.h"
#include "../../DotVisitor.h"


int ExpressionThis::Accept(Visitor* v)
{
    return v->Visit(this);
}
