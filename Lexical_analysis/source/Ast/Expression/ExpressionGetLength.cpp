//
// Created by nikolai on 22.10.19.
//

#include "ExpressionGetLength.h"
#include "../../DotVisitor.h"


int ExpressionGetLength::Accept(Visitor* v)
{
    return v->Visit(this);
}
