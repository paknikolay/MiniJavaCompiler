//
// Created by nikolai on 24.11.19.
//
#include "IRTNodeBase.h"
#include "../IRTDotVisitor.h"

int IRTNodeBase::Accept(Visitor *v) {
    // return v->Visit(this);
    return 0;
}


