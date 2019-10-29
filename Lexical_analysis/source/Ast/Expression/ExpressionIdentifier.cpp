//
// Created by nikolai on 22.10.19.
//

#include "ExpressionIdentifier.h"
#include "../../Visitor.h"


int ExpressionIdentifier::Accept(Visitor* v)
{
    return v->Visit(this);
}
