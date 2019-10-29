//
// Created by malik on 26.10.2019.
//

#include "Goal.h"
#include "../../Visitor.h"


int Goal::Accept(Visitor* v)
{
    return v->Visit(this);
}
