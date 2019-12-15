//
// Created by nikolai on 24.11.19.
//

#include "CJump.h"
#include "../IRTDotVisitor.h"

int CJump::Accept(Visitor *v) {
    return v->Visit(this);
}
