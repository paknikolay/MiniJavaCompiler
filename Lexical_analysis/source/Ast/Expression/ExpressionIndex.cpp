//
// Created by nikolai on 22.10.19.
//

#include "ExpressionIndex.h"
#include "../../Visitor.h"


int ExpressionIndex::Accept(Visitor* v)
{
    return v->Visit(this);
}
