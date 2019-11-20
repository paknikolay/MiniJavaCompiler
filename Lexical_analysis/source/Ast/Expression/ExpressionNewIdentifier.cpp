//
// Created by nikolai on 22.10.19.
//

#include "ExpressionNewIdentifier.h"
#include "../../DotVisitor.h"


int ExpressionNewIdentifier::Accept(Visitor* v)
{
    return v->Visit(this);
}
