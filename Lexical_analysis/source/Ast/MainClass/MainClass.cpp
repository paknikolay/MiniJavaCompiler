//
// Created by malik on 26.10.2019.
//

#include "MainClass.h"
#include "../../DotVisitor.h"


int MainClass::Accept(Visitor* v)
{
    return v->Visit(this);
}
