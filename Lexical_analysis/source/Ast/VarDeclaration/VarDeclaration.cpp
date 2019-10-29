//
// Created by malik on 26.10.2019.
//

#include "VarDeclaration.h"
#include "../../Visitor.h"


int VarDeclaration::Accept(Visitor* v)
{
    return v->Visit(this);
}
