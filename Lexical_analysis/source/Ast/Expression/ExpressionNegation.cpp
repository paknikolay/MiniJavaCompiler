//
// Created by nikolai on 22.10.19.
//

#include "ExpressionNegation.h"
#include "../../Visitor.h"


int ExpressionNegation::Accept(Visitor* v)
{
    return v->Visit(this);
}
