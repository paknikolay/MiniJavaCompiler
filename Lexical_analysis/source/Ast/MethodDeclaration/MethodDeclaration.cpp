//
// Created by nikolai on 26.10.19.
//

#include "MethodDeclaration.h"
#include "../../Visitor.h"


int MethodBody::Accept(Visitor* v)
{
    return v->Visit(this);
}

int MethodDeclaration::Accept(Visitor* v)
{
    return v->Visit(this);
}


