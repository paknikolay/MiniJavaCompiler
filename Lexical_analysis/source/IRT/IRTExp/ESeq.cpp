//
// Created by nikolai on 24.11.19.
//
#include "ESeq.h"
#include "../IRTDotVisitor.h"

int ESeq::Accept(Visitor *v) {
    return v->Visit(this);
}
