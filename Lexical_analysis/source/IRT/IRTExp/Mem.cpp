//
// Created by nikolai on 24.11.19.
//
#include "Mem.h"
#include "../IRTDotVisitor.h"

int Mem::Accept(Visitor *v) {
    return v->Visit(this);
}

