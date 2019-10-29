//
// Created by nikolai on 26.10.19.
//

#include "Statements.h"
#include "../../Visitor.h"


int StatementIf::Accept(Visitor* v)
{
    return v->Visit(this);
}

int StatementWhile::Accept(Visitor* v)
{
    return v->Visit(this);
}

int StatementAssign::Accept(Visitor* v)
{
    return v->Visit(this);
}

int StatementAssignContainerElement::Accept(Visitor* v)
{
    return v->Visit(this);
}

int StatementPrint::Accept(Visitor* v)
{
    return v->Visit(this);
}

int StatementSequence::Accept(Visitor* v)
{
    return v->Visit(this);
}
