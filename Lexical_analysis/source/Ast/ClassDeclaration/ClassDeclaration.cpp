//
// Created by malik on 26.10.2019.
//

#include "ClassDeclaration.h"
#include "../../Visitor.h"


int ClassDeclaration::Accept(Visitor* v)
{
    return v->Visit(this);
}
