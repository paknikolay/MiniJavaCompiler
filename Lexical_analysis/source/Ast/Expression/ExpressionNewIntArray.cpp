//
// Created by nikolai on 22.10.19.
//

#include "ExpressionNewIntArray.h"
#include "../../Visitor.h"


int ExpressionNewIntArray::Accept(Visitor* v)
{
    return v->Visit(this);
}
