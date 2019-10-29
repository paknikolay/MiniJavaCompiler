//
// Created by nikolai on 22.10.19.
//

#include "BaseNode.h"
#include "../Visitor.h"


int BaseNode::Accept(Visitor* v)
{
    return -1;
}