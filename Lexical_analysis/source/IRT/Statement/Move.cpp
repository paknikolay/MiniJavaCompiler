//
// Created by nikolai on 24.11.19.
//

#include "Move.h"
#include "../IRTDotVisitor.h"

int Move::Accept(Visitor *v) {
    return v->Visit(this);
}


