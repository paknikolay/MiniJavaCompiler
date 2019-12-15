//
// Created by nikolai on 24.11.19.
//
#include "BinOp.h"
#include "../IRTDotVisitor.h"

int BinOp::Accept(Visitor *v) {
    return v->Visit(this);
}
