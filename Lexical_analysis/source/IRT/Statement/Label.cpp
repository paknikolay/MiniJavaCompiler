//
// Created by nikolai on 24.11.19.
//
#include "Label.h"
#include "../IRTDotVisitor.h"

int Label::Accept(Visitor *v) {
    return v->Visit(this);
}

