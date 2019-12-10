//
// Created by nikolai on 24.11.19.
//
#include "Seq.h"
#include "../IRTDotVisitor.h"

int Seq::Accept(Visitor *v) {
    return v->Visit(this);
}

