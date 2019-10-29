//
// Created by nikolai on 22.10.19.
//

#include "ExpressionThis.h"
#include "../../Visitor.h"


int ExpressionThis::Accept(Visitor* v)
{
    return v->Visit(this);
}
