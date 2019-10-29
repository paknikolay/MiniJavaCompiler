//
// Created by nikolai on 22.10.19.
//

#include "ExpressionNewIdentifier.h"
#include "../../Visitor.h"


int ExpressionNewIdentifier::Accept(Visitor* v)
{
    return v->Visit(this);
}
