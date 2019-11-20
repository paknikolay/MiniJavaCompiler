//
// Created by nikolai on 22.10.19.
//

#include "BaseNode.h"
#include "../DotVisitor.h"


int BaseNode::Accept(Visitor* v)
{
    return -1;
}