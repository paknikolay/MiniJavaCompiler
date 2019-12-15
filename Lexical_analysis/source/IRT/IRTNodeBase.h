//
// Created by nikolai on 24.11.19.
//
#pragma once

#include "../Ast/BaseNode.h"

//class Visitor;

class IRTNodeBase : public BaseNode {

public:
    int Accept(Visitor* visitor);
};