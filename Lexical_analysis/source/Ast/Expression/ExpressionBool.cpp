//
// Created by nikolai on 22.10.19.
//

#include "ExpressionBool.h"
#include "../../DotVisitor.h"


int ExpressionBool::Accept(Visitor* v)
{
    return v->Visit(this);
}
