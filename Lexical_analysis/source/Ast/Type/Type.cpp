//
// Created by nikolai on 26.10.19.
//

#include "Type.h"
#include "../../DotVisitor.h"


int Type::Accept(Visitor* v)
{
    return v->Visit(this);
}
