//
// Created by nikolai on 24.11.19.
//
#include "Call.h"
#include "../IRTDotVisitor.h"

int Call::Accept(Visitor *v) {
    return v->Visit(this);
}

